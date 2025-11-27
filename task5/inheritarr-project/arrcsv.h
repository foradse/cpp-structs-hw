#ifndef ARRCSV_H
#define ARRCSV_H

#include "dynarr.h"
#include <string>

// Класс для вывода массива в CSV файл
class ArrCSV : public IntDynArray {
public:
    explicit ArrCSV(std::size_t n);
    ArrCSV(const ArrCSV& other);
    virtual ~ArrCSV() = default;
    
    // Переопределение виртуального метода для сохранения в csv файл
    void saveToFile() const override;

private:
    // Генерация имени файла с текущей датой и временем
    std::string generateFileName() const;
};

#endif // ARRCSV_H
