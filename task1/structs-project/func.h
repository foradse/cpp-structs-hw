#ifndef FUNC_H
#define FUNC_H

#include "structs.h"

// ===== Ввод-вывод и измерения окружности =====
void read_circle(Circle& c);              // ввод: x y r
void print_circle(const Circle& c);       // вывод: x y r
double circle_circumference(const Circle& c);  // длина окружности
double circle_area(const Circle& c);           // площадь круга

// ===== Ввод-вывод и измерения квадрата =====
void read_square(Square& s);              // ввод: x_left y_top side
void print_square(const Square& s);       // вывод: x_left y_top side
double square_perimeter(const Square& s);      // периметр квадрата
double square_area(const Square& s);           // площадь квадрата

// ===== Принадлежность точки фигуре =====
bool is_point_inside_circle_strict(const Point& p, const Circle& c);  // точка строго внутри окружности
bool is_point_on_circle(const Point& p, const Circle& c);             // точка на границе окружности

bool is_point_inside_square_strict(const Point& p, const Square& s);  // точка строго внутри квадрата
bool is_point_on_square(const Point& p, const Square& s);             // точка на границе квадрата

// ===== Пересечение фигур (пересечение границ) =====
bool circles_intersect_on_boundary(const Circle& a, const Circle& b);        // окружности пересекаются по границе
bool squares_intersect_on_boundary(const Square& a, const Square& b);        // квадраты пересекаются по границе
bool circle_square_intersect_on_boundary(const Circle& c, const Square& s);  // окружность и квадрат пересекаются по границе

// ===== Строгое вложение фигур (строго внутри, без касания) =====
bool circle_inside_circle_strict(const Circle& inner, const Circle& outer);  // окружность строго внутри окружности
bool square_inside_square_strict(const Square& inner, const Square& outer);  // квадрат строго внутри квадрата
bool square_inside_circle_strict(const Square& sq, const Circle& c);         // квадрат строго внутри окружности
bool circle_inside_square_strict(const Circle& c, const Square& s);         // окружность строго внутри квадрата

#endif // FUNC_H
