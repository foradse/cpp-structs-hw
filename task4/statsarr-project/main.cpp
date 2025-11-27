#include "statsarr.h"
#include <iostream>
#include <iomanip>

int main() {
    std::cout << "=== StatsArray demo ===\n\n";

    // Создание массива и заполнение значениями
    StatsArray arr(5);
    arr.set(0, 10);
    arr.set(1, -5);
    arr.set(2, 20);
    arr.set(3, 0);
    arr.set(4, 15);
    
    std::cout << "Array: ";
    arr.print();
    
    // Вычисление статистики
    std::cout << "\nStatistics:\n";
    std::cout << "  Average: " << std::fixed << std::setprecision(2) << arr.average() << "\n";
    std::cout << "  Median:  " << std::fixed << std::setprecision(2) << arr.median() << "\n";
    std::cout << "  Min:     " << arr.min() << "\n";
    std::cout << "  Max:     " << arr.max() << "\n";
    
    // Демонстрация с массивом нечетного размера
    std::cout << "\n=== Array with odd size ===\n";
    StatsArray arr2(7);
    arr2.set(0, 5);
    arr2.set(1, 2);
    arr2.set(2, 8);
    arr2.set(3, 1);
    arr2.set(4, 9);
    arr2.set(5, 3);
    arr2.set(6, 7);
    
    std::cout << "Array: ";
    arr2.print();
    std::cout << "  Median:  " << std::fixed << std::setprecision(2) << arr2.median() << "\n";
    
    // Демонстрация с массивом четного размера
    std::cout << "\n=== Array with even size ===\n";
    StatsArray arr3(4);
    arr3.set(0, 10);
    arr3.set(1, 5);
    arr3.set(2, 20);
    arr3.set(3, 15);
    
    std::cout << "Array: ";
    arr3.print();
    std::cout << "  Median:  " << std::fixed << std::setprecision(2) << arr3.median() << "\n";
    
    // Демонстрация с отрицательными значениями
    std::cout << "\n=== Array with negative values ===\n";
    StatsArray arr4(6);
    arr4.set(0, -10);
    arr4.set(1, -5);
    arr4.set(2, 0);
    arr4.set(3, 5);
    arr4.set(4, 10);
    arr4.set(5, -20);
    
    std::cout << "Array: ";
    arr4.print();
    std::cout << "  Average: " << std::fixed << std::setprecision(2) << arr4.average() << "\n";
    std::cout << "  Median:  " << std::fixed << std::setprecision(2) << arr4.median() << "\n";
    std::cout << "  Min:     " << arr4.min() << "\n";
    std::cout << "  Max:     " << arr4.max() << "\n";
    
    std::cout << "\nDone.\n";
    return 0;
}

