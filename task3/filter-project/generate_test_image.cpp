#include "image.h"
#include <iostream>
#include <random>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Генерация простого тестового изображения (градиент)
Image generateGradient(int width, int height) {
    Image img(width, height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Создаем градиент от черного к белому
            uint8_t value = static_cast<uint8_t>((x * 255) / width);
            img.set(x, y, value);
        }
    }
    return img;
}

// Генерация изображения с синусоидальным паттерном
Image generateSinePattern(int width, int height) {
    Image img(width, height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Синусоида с несколькими частотами
            double value = 128.0 + 127.0 * sin(2.0 * M_PI * x / 50.0) * cos(2.0 * M_PI * y / 50.0);
            img.set(x, y, static_cast<uint8_t>(value));
        }
    }
    return img;
}

// Добавление salt-and-pepper шума (импульсный шум)
Image addSaltAndPepperNoise(const Image& img, double noiseProbability) {
    Image noisy = img.copy();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> probDist(0.0, 1.0);
    std::uniform_int_distribution<int> valueDist(0, 255);
    
    for (int y = 0; y < noisy.height; ++y) {
        for (int x = 0; x < noisy.width; ++x) {
            if (probDist(gen) < noiseProbability) {
                // Случайно выбираем черный (0) или белый (255)
                uint8_t noiseValue = (probDist(gen) < 0.5) ? 0 : 255;
                noisy.set(x, y, noiseValue);
            }
        }
    }
    return noisy;
}

// Добавление гауссова шума
Image addGaussianNoise(const Image& img, double sigma) {
    Image noisy = img.copy();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> noiseDist(0.0, sigma);
    
    for (int y = 0; y < noisy.height; ++y) {
        for (int x = 0; x < noisy.width; ++x) {
            int originalValue = noisy.get(x, y);
            double noise = noiseDist(gen);
            int newValue = static_cast<int>(originalValue + noise);
            
            // Ограничиваем значения в диапазоне [0, 255]
            if (newValue < 0) newValue = 0;
            if (newValue > 255) newValue = 255;
            
            noisy.set(x, y, static_cast<uint8_t>(newValue));
        }
    }
    return noisy;
}

int main(int argc, char* argv[]) {
    std::cout << "=== Test Image Generator ===\n\n";
    
    int width = 640;
    int height = 480;
    std::string outputFile = "images/test_noisy.bmp";
    std::string pattern = "gradient"; // или "sine"
    double noiseLevel = 0.1; // 10% для salt-and-pepper
    
    // Парсинг аргументов
    if (argc >= 2) {
        pattern = argv[1];
    }
    if (argc >= 3) {
        noiseLevel = std::stod(argv[2]);
    }
    if (argc >= 4) {
        outputFile = argv[3];
    }
    
    std::cout << "Pattern: " << pattern << "\n";
    std::cout << "Noise level: " << noiseLevel << "\n";
    std::cout << "Output: " << outputFile << "\n\n";
    
    // Генерируем базовое изображение
    Image base;
    if (pattern == "sine" || pattern == "sin") {
        std::cout << "Generating sine wave pattern...\n";
        base = generateSinePattern(width, height);
    } else {
        std::cout << "Generating gradient pattern...\n";
        base = generateGradient(width, height);
    }
    
    // Сохраняем оригинал без шума
    std::string cleanFile = outputFile;
    size_t dotPos = cleanFile.find_last_of('.');
    if (dotPos != std::string::npos) {
        cleanFile = cleanFile.substr(0, dotPos) + "_clean.bmp";
    }
    base.saveToBMP(cleanFile);
    std::cout << "Saved clean image: " << cleanFile << "\n";
    
    // Добавляем salt-and-pepper шум
    std::cout << "Adding salt-and-pepper noise...\n";
    Image noisy = addSaltAndPepperNoise(base, noiseLevel);
    noisy.saveToBMP(outputFile);
    std::cout << "Saved noisy image: " << outputFile << "\n";
    
    // Также создаем версию с гауссовым шумом
    std::string gaussianFile = outputFile;
    dotPos = gaussianFile.find_last_of('.');
    if (dotPos != std::string::npos) {
        gaussianFile = gaussianFile.substr(0, dotPos) + "_gaussian.bmp";
    }
    std::cout << "Adding Gaussian noise...\n";
    Image gaussianNoisy = addGaussianNoise(base, 20.0); // sigma = 20
    gaussianNoisy.saveToBMP(gaussianFile);
    std::cout << "Saved Gaussian noisy image: " << gaussianFile << "\n";
    
    std::cout << "\n=== Done ===\n";
    std::cout << "You can now test filters with:\n";
    std::cout << "  ./filter.exe\n";
    
    return 0;
}

