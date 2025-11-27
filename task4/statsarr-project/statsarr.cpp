#include "statsarr.h"
#include <algorithm>
#include <stdexcept>

// Вычисление среднего значения
double StatsArray::average() const {
    if (size() == 0) {
        throw std::runtime_error("Cannot calculate average of empty array");
    }
    
    long long sum = 0;
    for (std::size_t i = 0; i < size(); ++i) {
        sum += get(i);
    }
    
    return static_cast<double>(sum) / static_cast<double>(size());
}

// Вычисление медианного значения
double StatsArray::median() const {
    if (size() == 0) {
        throw std::runtime_error("Cannot calculate median of empty array");
    }
    
    // Создаем копию массива для сортировки
    int* sorted_data = new int[size()];
    for (std::size_t i = 0; i < size(); ++i) {
        sorted_data[i] = get(i);
    }
    
    std::sort(sorted_data, sorted_data + size());
    
    double result;
    if (size() % 2 == 1) {
        // Нечетное количество элементов - берем средний
        result = static_cast<double>(sorted_data[size() / 2]);
    } else {
        // Четное количество элементов - среднее двух средних
        result = (static_cast<double>(sorted_data[size() / 2 - 1]) + 
                  static_cast<double>(sorted_data[size() / 2])) / 2.0;
    }
    
    delete[] sorted_data;
    return result;
}

// Вывод (возврат) наименьшего элемента
int StatsArray::min() const {
    if (size() == 0) {
        throw std::runtime_error("Cannot find minimum of empty array");
    }
    
    int min_val = get(0);
    for (std::size_t i = 1; i < size(); ++i) {
        int val = get(i);
        if (val < min_val) {
            min_val = val;
        }
    }
    
    return min_val;
}

// Вывод (возврат) наибольшего элемента
int StatsArray::max() const {
    if (size() == 0) {
        throw std::runtime_error("Cannot find maximum of empty array");
    }
    
    int max_val = get(0);
    for (std::size_t i = 1; i < size(); ++i) {
        int val = get(i);
        if (val > max_val) {
            max_val = val;
        }
    }
    
    return max_val;
}

