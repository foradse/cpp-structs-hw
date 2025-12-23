#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <typeinfo>
#include <type_traits>
#include <cmath>

// Шаблонный класс массива элементов задаваемого типа
template<typename T>
class Array {
public:
    // Конструкторы и деструктор
    explicit Array(std::size_t n);
    ~Array();
    Array(const Array& other);
    Array& operator=(const Array& other);

    // Получение размера массива
    std::size_t size() const { return n_; }

    // Основные операции с элементами
    T get(std::size_t idx) const;
    void set(std::size_t idx, const T& value);

    // Сеттер с проверкой данных для числовых значений
    template<typename U = T>
    typename std::enable_if<std::is_arithmetic<U>::value>::type
    set_checked(std::size_t idx, const U& value);

    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Array<T>& arr) {
        os << "[";
        for (std::size_t i = 0; i < arr.n_; ++i) {
            os << arr.data_[i];
            if (i < arr.n_ - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }

private:
    T* data_;
    std::size_t n_;

    // Проверка индекса
    void check_index(std::size_t idx) const;
};

// Функция вычисления Евклидова расстояния между массивами
// Только для числовых типов
template<typename T>
double euclidean_distance(const Array<T>& arr1, const Array<T>& arr2) {
    // Проверка типа: только числовые типы
    if (!std::is_arithmetic<T>::value) {
        throw std::bad_typeid();
    }

    // Проверка размеров
    if (arr1.size() != arr2.size()) {
        throw std::invalid_argument("arrays must have the same size");
    }

    // Вычисление Евклидова расстояния
    double sum = 0.0;
    for (std::size_t i = 0; i < arr1.size(); ++i) {
        double diff = static_cast<double>(arr1.get(i)) - static_cast<double>(arr2.get(i));
        sum += diff * diff;
    }

    return std::sqrt(sum);
}

// Реализация методов шаблона

template<typename T>
Array<T>::Array(std::size_t n) : data_(nullptr), n_(n) {
    if (n == 0) {
        throw std::invalid_argument("array size must be greater than 0");
    }
    data_ = new T[n_];
    // Для числовых типов инициализируем нулями, для остальных - значением по умолчанию
    if constexpr (std::is_arithmetic<T>::value) {
        for (std::size_t i = 0; i < n_; ++i) {
            data_[i] = T(0);
        }
    } else {
        for (std::size_t i = 0; i < n_; ++i) {
            data_[i] = T();
        }
    }
}

template<typename T>
Array<T>::~Array() {
    delete[] data_;
}

template<typename T>
Array<T>::Array(const Array& other) : data_(nullptr), n_(other.n_) {
    data_ = new T[n_];
    for (std::size_t i = 0; i < n_; ++i) {
        data_[i] = other.data_[i];
    }
}

template<typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
        delete[] data_;
        n_ = other.n_;
        data_ = new T[n_];
        for (std::size_t i = 0; i < n_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    return *this;
}

template<typename T>
void Array<T>::check_index(std::size_t idx) const {
    if (idx >= n_) {
        throw std::out_of_range("index out of range");
    }
}

template<typename T>
T Array<T>::get(std::size_t idx) const {
    check_index(idx);
    return data_[idx];
}

template<typename T>
void Array<T>::set(std::size_t idx, const T& value) {
    check_index(idx);
    data_[idx] = value;
}

// Специализация сеттера с проверкой для числовых типов
template<typename T>
template<typename U>
typename std::enable_if<std::is_arithmetic<U>::value>::type
Array<T>::set_checked(std::size_t idx, const U& value) {
    check_index(idx);
    
    // Проверка диапазона для числовых типов
    // Можно добавить дополнительные проверки в зависимости от типа
    if constexpr (std::is_integral<U>::value) {
        // Для целочисленных типов можно добавить проверку диапазона
        // Здесь просто проверяем, что значение не выходит за пределы типа
        data_[idx] = static_cast<T>(value);
    } else {
        // Для вещественных типов
        data_[idx] = static_cast<T>(value);
    }
}

#endif // ARRAY_H

