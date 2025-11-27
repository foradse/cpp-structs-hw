#ifndef DYNARR_H
#define DYNARR_H

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <string>

// Базовый класс динамического массива целых чисел
class IntDynArray {
public:
    // Ограничения на значения элементов
    static constexpr int MIN_VAL = -100;
    static constexpr int MAX_VAL =  100;

    // Конструкторы и деструктор
    explicit IntDynArray(std::size_t n);
    virtual ~IntDynArray();  // виртуальный деструктор для правильного полиморфизма
    IntDynArray(const IntDynArray& other);

    // Оператор присваивания удален для упрощения
    IntDynArray& operator=(const IntDynArray& other) = delete;

    // Получение размера массива
    std::size_t size() const { return n_; }

    // Основные операции с элементами
    int  get(std::size_t idx) const;                 // получение с проверкой границ
    void set(std::size_t idx, int value);            // установка с проверкой границ и диапазона [-100..100]

    // Операции с массивом
    void push_back(int value);                       // добавление в конец с проверкой диапазона и увеличением размера на 1

    // Поэлементные операции
    void add(const IntDynArray& other);              // поэлементное сложение, дополнение нулями
    void sub(const IntDynArray& other);              // поэлементное вычитание, дополнение нулями

    // Вывод массива
    virtual void print(std::ostream& os = std::cout) const;  // виртуальный метод вывода
    
    // Виртуальный метод для сохранения в файл
    virtual void saveToFile() const = 0;  // чисто виртуальный метод

protected:
    int* data_{nullptr};        // указатель на данные (защищен для доступа наследников)
    std::size_t n_{0};          // размер массива (защищен для доступа наследников)
};

#endif // DYNARR_H

