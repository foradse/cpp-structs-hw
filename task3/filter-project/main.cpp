#include "image.h"
#include "filters.h"
#include "similarity.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <cctype>

#ifdef _WIN32
#include <windows.h>
#endif

// Получить список всех BMP файлов в папке
std::vector<std::string> getBMPFiles(const std::string& folderPath) {
    std::vector<std::string> files;
    
    try {
        for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().string();
                std::string ext = entry.path().extension().string();
                // Преобразуем расширение в нижний регистр для сравнения
                std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
                if (ext == ".bmp") {
                    files.push_back(filename);
                }
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error accessing folder: " << e.what() << std::endl;
    }
    
    return files;
}

// Получить имя файла без пути
std::string getFilename(const std::string& filepath) {
    size_t pos = filepath.find_last_of("/\\");
    if (pos != std::string::npos) {
        return filepath.substr(pos + 1);
    }
    return filepath;
}

// Сохранить результаты в CSV файл
void saveResultsToCSV(const std::vector<std::vector<std::string>>& results, const std::string& filename) {
    std::ofstream csvFile(filename);
    if (!csvFile.is_open()) {
        std::cerr << "Error: Cannot create CSV file " << filename << std::endl;
        return;
    }
    
    // Заголовки CSV
    csvFile << "Image,Filter,FilterSize,MSE,PSNR,SSIM,Correlation\n";
    
    // Записываем данные
    for (const auto& row : results) {
        for (size_t i = 0; i < row.size(); ++i) {
            csvFile << row[i];
            if (i < row.size() - 1) {
                csvFile << ",";
            }
        }
        csvFile << "\n";
    }
    
    csvFile.close();
    std::cout << "Results saved to " << filename << std::endl;
}

int main(int argc, char* argv[]) {
    std::string inputFolder = "images";
    std::string outputFolder = "output";
    std::string csvFile = "results.csv";
    
    // Парсинг аргументов командной строки
    if (argc >= 2) {
        inputFolder = argv[1];
    }
    if (argc >= 3) {
        outputFolder = argv[2];
    }
    if (argc >= 4) {
        csvFile = argv[3];
    }
    
    std::cout << "=== Image Filtering and Similarity Analysis ===\n";
    std::cout << "Input folder: " << inputFolder << "\n";
    std::cout << "Output folder: " << outputFolder << "\n";
    std::cout << "CSV file: " << csvFile << "\n\n";
    
    // Создаем папку для выходных файлов, если её нет
    try {
        std::filesystem::create_directories(outputFolder);
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Warning: Cannot create output folder: " << e.what() << std::endl;
    }
    
    // Получаем список BMP файлов
    std::vector<std::string> bmpFiles = getBMPFiles(inputFolder);
    
    if (bmpFiles.empty()) {
        std::cerr << "Error: No BMP files found in folder " << inputFolder << std::endl;
        std::cerr << "Please create an 'images' folder and add BMP files to it." << std::endl;
        return 1;
    }
    
    std::cout << "Found " << bmpFiles.size() << " BMP file(s)\n\n";
    
    // Вектор для хранения результатов
    std::vector<std::vector<std::string>> results;
    
    // Обрабатываем каждое изображение
    for (const std::string& filepath : bmpFiles) {
        std::string filename = getFilename(filepath);
        std::cout << "Processing: " << filename << "\n";
        
        // Загружаем исходное изображение
        Image original;
        if (!original.loadFromBMP(filepath)) {
            std::cerr << "  Error: Cannot load " << filename << std::endl;
            continue;
        }
        
        std::cout << "  Size: " << original.width << "x" << original.height << "\n";
        
        // Параметры фильтров для тестирования
        std::vector<int> movingAvgSizes = {4, 8, 16, 32};
        std::vector<int> medianSizes = {3, 5, 7};
        
        // Применяем фильтр скользящего среднего
        for (int bufferSize : movingAvgSizes) {
            Image filtered = movingAverageFilter(original, bufferSize);
            
            // Сохраняем отфильтрованное изображение
            std::string outputName = outputFolder + "/" + filename;
            size_t dotPos = outputName.find_last_of('.');
            if (dotPos != std::string::npos) {
                outputName = outputName.substr(0, dotPos) + "_ma" + std::to_string(bufferSize) + ".bmp";
            } else {
                outputName += "_ma" + std::to_string(bufferSize) + ".bmp";
            }
            filtered.saveToBMP(outputName);
            
            // Вычисляем метрики схожести
            SimilarityMetrics metrics = calculateSimilarity(original, filtered);
            
            // Добавляем результаты в CSV
            std::vector<std::string> row;
            row.push_back(filename);
            row.push_back("MovingAverage");
            row.push_back(std::to_string(bufferSize));
            row.push_back(std::to_string(metrics.mse));
            row.push_back(std::to_string(metrics.psnr));
            row.push_back(std::to_string(metrics.ssim));
            row.push_back(std::to_string(metrics.correlation));
            results.push_back(row);
            
            std::cout << "  Moving Average (" << bufferSize << "): "
                      << "MSE=" << std::fixed << std::setprecision(2) << metrics.mse
                      << ", PSNR=" << std::setprecision(2) << metrics.psnr
                      << ", SSIM=" << std::setprecision(4) << metrics.ssim
                      << ", Corr=" << std::setprecision(4) << metrics.correlation << "\n";
        }
        
        // Применяем медианный фильтр
        for (int filterSize : medianSizes) {
            Image filtered = medianFilter(original, filterSize);
            
            // Сохраняем отфильтрованное изображение
            std::string outputName = outputFolder + "/" + filename;
            size_t dotPos = outputName.find_last_of('.');
            if (dotPos != std::string::npos) {
                outputName = outputName.substr(0, dotPos) + "_median" + std::to_string(filterSize) + ".bmp";
            } else {
                outputName += "_median" + std::to_string(filterSize) + ".bmp";
            }
            filtered.saveToBMP(outputName);
            
            // Вычисляем метрики схожести
            SimilarityMetrics metrics = calculateSimilarity(original, filtered);
            
            // Добавляем результаты в CSV
            std::vector<std::string> row;
            row.push_back(filename);
            row.push_back("Median");
            row.push_back(std::to_string(filterSize));
            row.push_back(std::to_string(metrics.mse));
            row.push_back(std::to_string(metrics.psnr));
            row.push_back(std::to_string(metrics.ssim));
            row.push_back(std::to_string(metrics.correlation));
            results.push_back(row);
            
            std::cout << "  Median (" << filterSize << "): "
                      << "MSE=" << std::fixed << std::setprecision(2) << metrics.mse
                      << ", PSNR=" << std::setprecision(2) << metrics.psnr
                      << ", SSIM=" << std::setprecision(4) << metrics.ssim
                      << ", Corr=" << std::setprecision(4) << metrics.correlation << "\n";
        }
        
        std::cout << "\n";
    }
    
    // Сохраняем результаты в CSV
    saveResultsToCSV(results, csvFile);
    
    std::cout << "\n=== Processing complete ===\n";
    std::cout << "Processed " << bmpFiles.size() << " image(s)\n";
    std::cout << "Generated " << results.size() << " result(s)\n";
    
    return 0;
}

