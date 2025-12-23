#include "array.h"
#include <iostream>
#include <string>

int main() {
    std::cout << "=== Template Array Demo ===\n\n";

    // Тест 1: Массив целых чисел
    std::cout << "Test 1: Integer array\n";
    try {
        Array<int> arr1(5);
        arr1.set(0, 10);
        arr1.set(1, 20);
        arr1.set(2, 30);
        arr1.set(3, 40);
        arr1.set(4, 50);
        
        std::cout << "arr1: " << arr1 << "\n";
        
        // Использование set_checked для числовых типов
        arr1.set_checked(0, 15);
        std::cout << "arr1 after set_checked(0, 15): " << arr1 << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    // Тест 2: Массив вещественных чисел
    std::cout << "\nTest 2: Double array\n";
    try {
        Array<double> arr2(3);
        arr2.set(0, 1.5);
        arr2.set(1, 2.7);
        arr2.set(2, 3.9);
        
        std::cout << "arr2: " << arr2 << "\n";
        
        arr2.set_checked(1, 2.5);
        std::cout << "arr2 after set_checked(1, 2.5): " << arr2 << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    // Тест 3: Массив строк (не числовой тип)
    std::cout << "\nTest 3: String array\n";
    try {
        Array<std::string> arr3(3);
        arr3.set(0, "hello");
        arr3.set(1, "world");
        arr3.set(2, "test");
        
        std::cout << "arr3: " << arr3 << "\n";
        
        // set_checked недоступен для нечисловых типов (компилятор выдаст ошибку)
        // arr3.set_checked(0, "new"); // Это не скомпилируется
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    // Тест 4: Евклидово расстояние между числовыми массивами
    std::cout << "\nTest 4: Euclidean distance between numeric arrays\n";
    try {
        Array<int> arr4(3);
        arr4.set(0, 1);
        arr4.set(1, 2);
        arr4.set(2, 3);
        
        Array<int> arr5(3);
        arr5.set(0, 4);
        arr5.set(1, 5);
        arr5.set(2, 6);
        
        std::cout << "arr4: " << arr4 << "\n";
        std::cout << "arr5: " << arr5 << "\n";
        
        double dist = euclidean_distance(arr4, arr5);
        std::cout << "Euclidean distance: " << dist << "\n";
        
        // Тест с вещественными числами
        Array<double> arr6(2);
        arr6.set(0, 1.0);
        arr6.set(1, 2.0);
        
        Array<double> arr7(2);
        arr7.set(0, 3.0);
        arr7.set(1, 4.0);
        
        std::cout << "\narr6: " << arr6 << "\n";
        std::cout << "arr7: " << arr7 << "\n";
        
        double dist2 = euclidean_distance(arr6, arr7);
        std::cout << "Euclidean distance: " << dist2 << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    // Тест 5: Попытка вычислить расстояние для нечисловых типов
    std::cout << "\nTest 5: Euclidean distance for non-numeric types (should throw std::bad_typeid)\n";
    try {
        Array<std::string> arr8(2);
        arr8.set(0, "a");
        arr8.set(1, "b");
        
        Array<std::string> arr9(2);
        arr9.set(0, "c");
        arr9.set(1, "d");
        
        double dist = euclidean_distance(arr8, arr9);
        std::cout << "Distance: " << dist << "\n";
    } catch (const std::bad_typeid& e) {
        std::cout << "Caught std::bad_typeid (expected): non-numeric type\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    // Тест 6: Попытка вычислить расстояние для массивов разного размера
    std::cout << "\nTest 6: Euclidean distance for arrays of different sizes (should throw std::invalid_argument)\n";
    try {
        Array<int> arr10(3);
        arr10.set(0, 1);
        arr10.set(1, 2);
        arr10.set(2, 3);
        
        Array<int> arr11(2);
        arr11.set(0, 4);
        arr11.set(1, 5);
        
        double dist = euclidean_distance(arr10, arr11);
        std::cout << "Distance: " << dist << "\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught std::invalid_argument (expected): " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    // Тест 7: Копирование и присваивание
    std::cout << "\nTest 7: Copy constructor and assignment\n";
    try {
        Array<int> arr12(3);
        arr12.set(0, 10);
        arr12.set(1, 20);
        arr12.set(2, 30);
        
        Array<int> arr13 = arr12; // Конструктор копирования
        std::cout << "arr12: " << arr12 << "\n";
        std::cout << "arr13 (copy): " << arr13 << "\n";
        
        Array<int> arr14(2);
        arr14 = arr12; // Оператор присваивания
        std::cout << "arr14 (assigned): " << arr14 << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    std::cout << "\n=== Done ===\n";
    return 0;
}

