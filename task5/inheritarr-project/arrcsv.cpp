#include "arrcsv.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <ctime>

// Конструктор
ArrCSV::ArrCSV(std::size_t n) : IntDynArray(n) {}

// Конструктор копирования
ArrCSV::ArrCSV(const ArrCSV& other) : IntDynArray(other) {}

// Генерация имени файла с текущей датой и временем
std::string ArrCSV::generateFileName() const {
    auto now = std::time(nullptr);
    std::tm* tm = std::localtime(&now);
    
    std::ostringstream oss;
    oss << std::setfill('0')
        << std::setw(4) << (tm->tm_year + 1900)
        << std::setw(2) << (tm->tm_mon + 1)
        << std::setw(2) << tm->tm_mday
        << "_"
        << std::setw(2) << tm->tm_hour
        << std::setw(2) << tm->tm_min
        << std::setw(2) << tm->tm_sec
        << ".csv";
    return oss.str();
}

// Сохранение массива в CSV файл
void ArrCSV::saveToFile() const {
    std::string filename = generateFileName();
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    
    // Вывод элементов массива в CSV формат (через запятую)
    for (std::size_t i = 0; i < n_; ++i) {
        if (i) file << ',';  // запятая между элементами
        file << data_[i];
    }
    file << '\n';
    
    file.close();
    std::cout << "Array saved to file: " << filename << std::endl;
}
