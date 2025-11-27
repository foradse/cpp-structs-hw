# C++ Dynamic Array Inheritance Project

Практическое задание 5 - Наследование классов

## Описание

Проект демонстрирует наследование классов в C++. Базовый класс `IntDynArray` (динамический массив целых чисел из ПЗ 2) используется как родительский класс для двух производных классов:

- **ArrTxt** - класс для сохранения массива в текстовый файл (.txt)
- **ArrCSV** - класс для сохранения массива в CSV файл (.csv)

Имя файла формируется автоматически на основе текущей даты и времени в формате: `YYYYMMDD_HHMMSS.txt` или `YYYYMMDD_HHMMSS.csv`

## Структура проекта

- `dynarr.h` / `dynarr.cpp` - базовый класс IntDynArray
- `arrtxt.h` / `arrtxt.cpp` - класс ArrTxt для вывода в txt файл
- `arrcsv.h` / `arrcsv.cpp` - класс ArrCSV для вывода в csv файл
- `main.cpp` - демонстрация работы классов
- `Makefile` - файл для сборки проекта

## Сборка

Проект собирается через **MSYS**:

```bash
make
./inheritarr.exe
```

Или вручную:

```bash
g++ -std=c++17 -O2 -Wall -Wextra -Wpedantic main.cpp dynarr.cpp arrtxt.cpp arrcsv.cpp -o inheritarr.exe
```

## Использование

После запуска программы будут созданы файлы с текущей датой и временем:
- Файлы `.txt` - элементы массива разделены пробелами
- Файлы `.csv` - элементы массива разделены запятыми

## Пример

```cpp
// Создание массива ArrTxt
ArrTxt txtArray(5);
txtArray.set(0, 10);
txtArray.set(1, -5);
txtArray.saveToFile();  // Создаст файл типа 20231215_143022.txt

// Создание массива ArrCSV
ArrCSV csvArray(4);
csvArray.set(0, 1);
csvArray.set(1, 2);
csvArray.saveToFile();  // Создаст файл типа 20231215_143022.csv

// Демонстрация полиморфизма
IntDynArray* arr = new ArrTxt(3);
arr->saveToFile();  // Виртуальный вызов метода
delete arr;
```

## Очистка

Для удаления скомпилированных файлов и созданных txt/csv файлов:

```bash
make clean
```

