#ifndef STATSARR_H
#define STATSARR_H

#include "../task2/dynarr-project/dynarr.h"
#include <cstddef>

// Класс, наследующий IntDynArray с дополнительными статистическими методами
class StatsArray : public IntDynArray {
public:
    // Используем конструкторы базового класса
    using IntDynArray::IntDynArray;

    // Вычисление среднего значения
    double average() const;

    // Вычисление медианного значения
    double median() const;

    // Вывод (возврат) наименьшего элемента
    int min() const;

    // Вывод (возврат) наибольшего элемента
    int max() const;
};

#endif // STATSARR_H

