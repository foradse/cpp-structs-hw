#ifndef ARRTXT_H
#define ARRTXT_H

#include "dynarr.h"
#include <string>

// Класс для вывода массива в текстовый файл
class ArrTxt : public IntDynArray {
public:
    explicit ArrTxt(std::size_t n);
    ArrTxt(const ArrTxt& other);
    virtual ~ArrTxt() = default;
    
    // Переопределение виртуального метода для сохранения в txt файл
    void saveToFile() const override;

private:
    // Генерация имени файла с текущей датой и временем
    std::string generateFileName() const;
};

#endif // ARRTXT_H
