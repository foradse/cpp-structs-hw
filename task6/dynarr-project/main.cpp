#include "dynarr.h"
#include <iostream>

int main() {
    std::cout << "=== IntDynArray demo with exceptions ===\n\n";

    // Создание динамического массива A размером 3
    IntDynArray a(3);
    a.set(0, 10);
    a.set(1, -5);
    a.set(2, 100);
    std::cout << "A: "; a.print();

    // Добавление элемента в конец массива
    a.push_back(0);
    std::cout << "A after push_back(0): "; a.print();

    // Создание массива B и заполнение его значениями 0, 1, 2, 3, 4
    IntDynArray b(5);
    for (std::size_t i = 0; i < b.size(); ++i) b.set(i, (int)i); // 0 1 2 3 4
    std::cout << "B: "; b.print();

    // Поэлементное сложение массивов (B длиннее, лишние элементы считаются как 0)
    a.add(b); // add elementwise; B is longer, extra elements treated as 0 for A
    std::cout << "A = A + B: "; a.print();

    // Поэлементное вычитание массивов
    a.sub(b);
    std::cout << "A = A - B: "; a.print();

    // Копирование массива через конструктор копирования
    IntDynArray c = a; // copy constructor
    std::cout << "C (copy of A): "; c.print();

    // Демонстрация обработки исключений
    std::cout << "\n=== Exception handling demo ===\n\n";

    // Тест 1: std::out_of_range при обращении по несуществующему индексу (get)
    std::cout << "Test 1: std::out_of_range on get() with invalid index\n";
    try {
        int val = a.get(100);  // индекс вне диапазона
        std::cout << "Value: " << val << "\n";
    } catch (const std::out_of_range& e) {
        std::cout << "Caught std::out_of_range: " << e.what() << "\n";
    }

    // Тест 2: std::out_of_range при установке значения по несуществующему индексу (set)
    std::cout << "\nTest 2: std::out_of_range on set() with invalid index\n";
    try {
        a.set(100, 1);  // индекс вне диапазона
        std::cout << "Value set successfully\n";
    } catch (const std::out_of_range& e) {
        std::cout << "Caught std::out_of_range: " << e.what() << "\n";
    }

    // Тест 3: std::invalid_argument при попытке присвоить значение вне диапазона -100..100
    std::cout << "\nTest 3: std::invalid_argument on set() with value > 100\n";
    try {
        a.set(0, 200);  // значение вне диапазона
        std::cout << "Value set successfully\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught std::invalid_argument: " << e.what() << "\n";
    }

    // Тест 4: std::invalid_argument при попытке присвоить значение < -100
    std::cout << "\nTest 4: std::invalid_argument on set() with value < -100\n";
    try {
        a.set(0, -150);  // значение вне диапазона
        std::cout << "Value set successfully\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught std::invalid_argument: " << e.what() << "\n";
    }

    // Тест 5: std::invalid_argument при push_back с недопустимым значением
    std::cout << "\nTest 5: std::invalid_argument on push_back() with value > 100\n";
    try {
        a.push_back(101);  // значение вне диапазона
        std::cout << "Value pushed successfully\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught std::invalid_argument: " << e.what() << "\n";
    }

    // Тест 6: Успешные операции с граничными значениями
    std::cout << "\nTest 6: Successful operations with boundary values\n";
    try {
        a.set(0, -100);  // минимальное допустимое значение
        a.set(1, 100);   // максимальное допустимое значение
        std::cout << "Boundary values set successfully\n";
        std::cout << "A: "; a.print();
    } catch (const std::exception& e) {
        std::cout << "Unexpected exception: " << e.what() << "\n";
    }

    std::cout << "\nDone.\n";
    return 0;
}

