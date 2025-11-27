#include "arrtxt.h"
#include "arrcsv.h"
#include <iostream>

int main() {
    std::cout << "=== IntDynArray Inheritance Demo ===\n\n";
    
    // Создание массива ArrTxt
    std::cout << "1. Creating ArrTxt array:\n";
    ArrTxt txtArray(5);
    txtArray.set(0, 10);
    txtArray.set(1, -5);
    txtArray.set(2, 42);
    txtArray.set(3, 0);
    txtArray.set(4, 100);
    
    std::cout << "Array contents: ";
    txtArray.print();
    
    // Сохранение в txt файл
    std::cout << "\n2. Saving ArrTxt to file:\n";
    txtArray.saveToFile();
    
    // Создание массива ArrCSV
    std::cout << "\n3. Creating ArrCSV array:\n";
    ArrCSV csvArray(4);
    csvArray.set(0, 1);
    csvArray.set(1, 2);
    csvArray.set(2, 3);
    csvArray.set(3, -10);
    
    std::cout << "Array contents: ";
    csvArray.print();
    
    // Сохранение в csv файл
    std::cout << "\n4. Saving ArrCSV to file:\n";
    csvArray.saveToFile();
    
    // Демонстрация полиморфизма
    std::cout << "\n5. Demonstrating polymorphism:\n";
    IntDynArray* arrays[2];
    arrays[0] = new ArrTxt(3);
    arrays[0]->set(0, 7);
    arrays[0]->set(1, 8);
    arrays[0]->set(2, 9);
    
    arrays[1] = new ArrCSV(3);
    arrays[1]->set(0, 77);
    arrays[1]->set(1, 88);
    arrays[1]->set(2, 99);
    
    for (int i = 0; i < 2; i++) {
        std::cout << "Array " << i + 1 << ": ";
        arrays[i]->print();
        arrays[i]->saveToFile();
        delete arrays[i];
    }
    
    std::cout << "\nDone.\n";
    return 0;
}
