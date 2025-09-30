#include "dynarr.h"
#include <iostream>

int main() {
    std::cout << "=== IntDynArray demo ===\n";

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

    // Демонстрация проверки границ/диапазонов (раскомментируйте для просмотра исключений)
    // a.set(100, 1);              // out_of_range
    // a.set(0, 200);              // invalid_argument (range)
    // std::cout << a.get(100);    // out_of_range

    std::cout << "Done.\n";
    return 0;
}
