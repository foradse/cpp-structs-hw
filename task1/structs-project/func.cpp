#include "func.h"
#include <algorithm>

// ================== Ввод-вывод и измерения окружности ==================

// Чтение окружности с консоли
void read_circle(Circle& c) {
    // Читает: x y r (координаты центра и радиус)
    std::cin >> c.center.x >> c.center.y >> c.r;
}

// Вывод окружности на консоль
void print_circle(const Circle& c) {
    std::cout << std::fixed << std::setprecision(6)
              << "center=(" << c.center.x << ", " << c.center.y << "), r=" << c.r;
}

// Вычисление длины окружности
double circle_circumference(const Circle& c) {
    return 2.0 * PI * c.r;
}

// Вычисление площади круга
double circle_area(const Circle& c) {
    return PI * c.r * c.r;
}

// ================== Ввод-вывод и измерения квадрата ==================

// Чтение квадрата с консоли
void read_square(Square& s) {
    // Читает: x_left y_top side (координаты левого верхнего угла и длина стороны)
    std::cin >> s.topLeft.x >> s.topLeft.y >> s.side;
}

// Вывод квадрата на консоль
void print_square(const Square& s) {
    std::cout << std::fixed << std::setprecision(6)
              << "topLeft=(" << s.topLeft.x << ", " << s.topLeft.y << "), side=" << s.side;
}

// Вычисление периметра квадрата
double square_perimeter(const Square& s) {
    return 4.0 * s.side;
}

// Вычисление площади квадрата
double square_area(const Square& s) {
    return s.side * s.side;
}

// ================== Принадлежность точки фигуре ==================

// Строго внутри окружности (не на границе)
bool is_point_inside_circle_strict(const Point& p, const Circle& c) {
    double d = dist(p, c.center);
    return less_with_eps(d, c.r); // d < r - eps
}

// На границе окружности
bool is_point_on_circle(const Point& p, const Circle& c) {
    double d = dist(p, c.center);
    return almost_equal(d, c.r);
}

// Строго внутри квадрата (выровненного по осям), не на границах
bool is_point_inside_square_strict(const Point& p, const Square& s) {
    // Внутри означает: x в (L, R) и y в (B, T)
    return greater_with_eps(p.x, left(s)) &&
           less_with_eps(p.x, right(s)) &&
           greater_with_eps(p.y, bottom(s)) &&
           less_with_eps(p.y, top(s));
}

// На границе квадрата (ребрах), включая углы, с учетом EPS
bool is_point_on_square(const Point& p, const Square& s) {
    bool on_left   = almost_equal(p.x, left(s))   && p.y <= top(s)+EPS && p.y >= bottom(s)-EPS;
    bool on_right  = almost_equal(p.x, right(s))  && p.y <= top(s)+EPS && p.y >= bottom(s)-EPS;
    bool on_top    = almost_equal(p.y, top(s))    && p.x >= left(s)-EPS && p.x <= right(s)+EPS;
    bool on_bottom = almost_equal(p.y, bottom(s)) && p.x >= left(s)-EPS && p.x <= right(s)+EPS;
    return on_left || on_right || on_top || on_bottom;
}

// ================== Пересечение фигур (по границе) ==================
// "Пересечение" здесь означает: существует хотя бы одна общая точка границы.
// Если одна фигура строго внутри другой без касания границ, НЕ пересекаются.

// Пересечение окружностей по границе
bool circles_intersect_on_boundary(const Circle& a, const Circle& b) {
    double d = dist(a.center, b.center);
    double rsum = a.r + b.r;
    double rdiff = std::fabs(a.r - b.r);

    // Не пересекаются
    if (greater_with_eps(d, rsum)) return false;

    // Одна строго внутри другой без касания
    if (less_with_eps(d, rdiff)) return false;

    // Иначе границы либо касаются (касательная), либо пересекаются
    return true;
}

// Пересечение квадратов по границе (выровненных по осям)
bool squares_intersect_on_boundary(const Square& A, const Square& B) {
    // Быстрая проверка на непересечение (нет перекрытия даже по ребрам)
    if (less_with_eps(right(A), left(B)) || less_with_eps(right(B), left(A)) ||
        less_with_eps(top(A), bottom(B)) || less_with_eps(top(B), bottom(A))) {
        return false;
    }

    // Строгое вложение (A строго внутри B без касания)
    bool A_inside_B_strict =
        greater_with_eps(left(A), left(B)) &&
        less_with_eps(right(A), right(B)) &&
        less_with_eps(top(A), top(B)) &&
        greater_with_eps(bottom(A), bottom(B));

    bool B_inside_A_strict =
        greater_with_eps(left(B), left(A)) &&
        less_with_eps(right(B), right(A)) &&
        less_with_eps(top(B), top(A)) &&
        greater_with_eps(bottom(B), bottom(A));

    if (A_inside_B_strict || B_inside_A_strict) return false;

    // Иначе они либо касаются по ребрам/углам, либо перекрываются, пересекая границы
    return true;
}

// Пересечение окружности и квадрата по границе
bool circle_square_intersect_on_boundary(const Circle& c, const Square& s) {
    // Быстрая проверка на непересечение с использованием расстояния от окружности до прямоугольника
    double cx = c.center.x, cy = c.center.y;
    double L = left(s), R = right(s), T = top(s), B = bottom(s);

    // Расстояние от центра окружности до прямоугольника (0 если внутри проекции)
    double dx = 0.0;
    if (cx < L - EPS) dx = L - cx;
    else if (cx > R + EPS) dx = cx - R;

    double dy = 0.0;
    if (cy < B - EPS) dy = B - cy;
    else if (cy > T + EPS) dy = cy - T;

    double dmin = std::sqrt(dx*dx + dy*dy);
    if (greater_with_eps(dmin, c.r)) {
        // Центр достаточно далеко -> нет касания/перекрытия
        return false;
    }

    // Исключаем строгие вложения (без контакта границ)
    // 1) Квадрат строго внутри окружности (все четыре угла строго внутри)
    if (square_inside_circle_strict(s, c)) return false;

    // 2) Окружность строго внутри квадрата (центр строго внутри и r < мин. расстояние до ребер - EPS)
    if (circle_inside_square_strict(c, s)) return false;

    // Иначе они либо касаются, либо пересекают границы
    return true;
}

// ================== Строгое вложение фигур ==================

// Окружность строго внутри окружности
bool circle_inside_circle_strict(const Circle& inner, const Circle& outer) {
    double d = dist(inner.center, outer.center);
    // d + r_inner < r_outer  (строго, с EPS)
    return less_with_eps(d + inner.r, outer.r);
}

// Квадрат строго внутри квадрата
bool square_inside_square_strict(const Square& inner, const Square& outer) {
    return greater_with_eps(left(inner), left(outer)) &&
           less_with_eps(right(inner), right(outer)) &&
           less_with_eps(top(inner), top(outer)) &&
           greater_with_eps(bottom(inner), bottom(outer));
}

// Квадрат строго внутри окружности
bool square_inside_circle_strict(const Square& sq, const Circle& c) {
    // Все четыре угла строго внутри окружности
    Point p1{left(sq),  top(sq)};
    Point p2{right(sq), top(sq)};
    Point p3{right(sq), bottom(sq)};
    Point p4{left(sq),  bottom(sq)};

    return is_point_inside_circle_strict(p1, c) &&
           is_point_inside_circle_strict(p2, c) &&
           is_point_inside_circle_strict(p3, c) &&
           is_point_inside_circle_strict(p4, c);
}

// Окружность строго внутри квадрата
bool circle_inside_square_strict(const Circle& c, const Square& s) {
    // Центр строго внутри и радиус строго меньше минимального расстояния до ребер
    if (!is_point_inside_square_strict(c.center, s)) return false;
    double dL = c.center.x - left(s);
    double dR = right(s) - c.center.x;
    double dT = top(s) - c.center.y;
    double dB = c.center.y - bottom(s);
    double dmin = std::min(std::min(dL, dR), std::min(dT, dB));
    return less_with_eps(c.r, dmin);
}
