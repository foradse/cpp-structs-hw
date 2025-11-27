#include "arrtxt.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <ctime>

// Конструктор
ArrTxt::ArrTxt(std::size_t n) : IntDynArray(n) {}

// Конструктор копирования
ArrTxt::ArrTxt(const ArrTxt& other) : IntDynArray(other) {}

// Генерация имени файла с текущей датой и временем
std::string ArrTxt::generateFileName() const {
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
        << ".txt";
    return oss.str();
}

// Сохранение массива в текстовый файл
void ArrTxt::saveToFile() const {
    std::string filename = generateFileName();
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    
    // Вывод элементов массива в файл
    for (std::size_t i = 0; i < n_; ++i) {
        if (i) file << ' ';  // пробел между элементами
        file << data_[i];
    }
    file << '\n';
    
    file.close();
    std::cout << "Array saved to file: " << filename << std::endl;
}
