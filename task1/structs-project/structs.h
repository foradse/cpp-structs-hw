#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <cmath>
#include <iomanip>

// ===== Утилиты для работы с числами =====
constexpr double EPS = 1e-5;  // Точность для сравнения чисел с плавающей точкой
constexpr double PI  = 3.14;  // Константа π

// Проверка на равенство с учетом погрешности
inline bool almost_equal(double a, double b, double eps = EPS) {
    return std::fabs(a - b) <= eps;
}
// Строгое сравнение "меньше" с учетом погрешности
inline bool less_with_eps(double a, double b, double eps = EPS) {
    return a < b - eps;
}
// Сравнение "меньше или равно" с учетом погрешности
inline bool less_equal_with_eps(double a, double b, double eps = EPS) {
    return a <= b + eps;
}
// Строгое сравнение "больше" с учетом погрешности
inline bool greater_with_eps(double a, double b, double eps = EPS) {
    return a > b + eps;
}
// Сравнение "больше или равно" с учетом погрешности
inline bool greater_equal_with_eps(double a, double b, double eps = EPS) {
    return a >= b - eps;
}

// ===== Геометрические примитивы =====
// Точка на плоскости
struct Point {
    double x{};  // Координата X
    double y{};  // Координата Y
};

// Окружность
struct Circle {
    Point center{};  // Центр окружности
    double r{};      // Радиус
};

// Квадрат (выровненный по осям)
struct Square {
    // Квадрат, выровненный по осям. Храним левый верхний угол и длину стороны.
    Point topLeft{}; // (x_left, y_top) - левый верхний угол
    double side{};   // Длина стороны
};

// ===== Базовые утилиты ввода-вывода (объявлены здесь, определены inline для удобства) =====
// Чтение точки с консоли
inline void read_point(Point& p) {
    // Читает: x y
    std::cin >> p.x >> p.y;
}
// Вывод точки на консоль
inline void print_point(const Point& p) {
    std::cout << std::fixed << std::setprecision(6)
              << "(" << p.x << ", " << p.y << ")";
}

// Вспомогательные функции для расстояний и границ прямоугольника
// Квадрат расстояния между двумя точками
inline double dist2(const Point& a, const Point& b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return dx*dx + dy*dy;
}
// Расстояние между двумя точками
inline double dist(const Point& a, const Point& b) {
    return std::sqrt(dist2(a, b));
}

// Удобные функции для работы с квадратом
inline double left(const Square& s)   { return s.topLeft.x; }                    // Левая граница
inline double right(const Square& s)  { return s.topLeft.x + s.side; }           // Правая граница
inline double top(const Square& s)    { return s.topLeft.y; }                    // Верхняя граница
inline double bottom(const Square& s) { return s.topLeft.y - s.side; }           // Нижняя граница

// Ограничение значения в заданном диапазоне
inline double clamp(double v, double lo, double hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

#endif // STRUCTS_H
