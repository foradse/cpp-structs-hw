#include "structs.h"
#include "func.h"
#include <iostream>

int main() {
    std::cout << std::fixed << std::setprecision(6);

    std::cout << "=== Demo: Points, Circles, Squares ===\n";
    std::cout << "EPS = " << EPS << " (points closer than EPS considered coincident)\n\n";

    // Чтение точки
    Point p;
    std::cout << "Enter point P: x y\n> ";
    read_point(p);

    // Чтение окружности
    Circle c1;
    std::cout << "Enter circle C1: center_x center_y radius\n> ";
    read_circle(c1);

    // Чтение квадрата
    Square s1;
    std::cout << "Enter square S1: left_x top_y side\n> ";
    read_square(s1);

    std::cout << "\nYou entered:\n";
    std::cout << "P = "; print_point(p); std::cout << "\n";
    std::cout << "C1 = "; print_circle(c1); std::cout << "\n";
    std::cout << "S1 = "; print_square(s1); std::cout << "\n\n";

    std::cout << "Circle C1: length = " << circle_circumference(c1)
              << ", area = " << circle_area(c1) << "\n";
    std::cout << "Square S1: perimeter = " << square_perimeter(s1)
              << ", area = " << square_area(s1) << "\n\n";

    // Тесты принадлежности точки
    std::cout << "[Point membership]\n";
    std::cout << "P inside C1 (strict)? " << (is_point_inside_circle_strict(p, c1) ? "YES" : "NO") << "\n";
    std::cout << "P on C1? " << (is_point_on_circle(p, c1) ? "YES" : "NO") << "\n";
    std::cout << "P inside S1 (strict)? " << (is_point_inside_square_strict(p, s1) ? "YES" : "NO") << "\n";
    std::cout << "P on S1? " << (is_point_on_square(p, s1) ? "YES" : "NO") << "\n\n";

    // Чтение второй окружности и квадрата для тестов пересечений/вложений
    Circle c2;
    Square s2;
    std::cout << "Enter circle C2: center_x center_y radius\n> ";
    read_circle(c2);
    std::cout << "Enter square S2: left_x top_y side\n> ";
    read_square(s2);

    std::cout << "\nC2 = "; print_circle(c2); std::cout << "\n";
    std::cout << "S2 = "; print_square(s2); std::cout << "\n\n";

    // Пересечения по границе
    std::cout << "[Boundary intersections]\n";
    std::cout << "C1 vs C2 intersect on boundary? "
              << (circles_intersect_on_boundary(c1, c2) ? "YES" : "NO") << "\n";
    std::cout << "S1 vs S2 intersect on boundary? "
              << (squares_intersect_on_boundary(s1, s2) ? "YES" : "NO") << "\n";
    std::cout << "C1 vs S1 intersect on boundary? "
              << (circle_square_intersect_on_boundary(c1, s1) ? "YES" : "NO") << "\n";
    std::cout << "C2 vs S2 intersect on boundary? "
              << (circle_square_intersect_on_boundary(c2, s2) ? "YES" : "NO") << "\n\n";

    // Строгие вложения
    std::cout << "[Strict containments (first inside second)]\n";
    std::cout << "C1 inside C2? " << (circle_inside_circle_strict(c1, c2) ? "YES" : "NO") << "\n";
    std::cout << "S1 inside S2? " << (square_inside_square_strict(s1, s2) ? "YES" : "NO") << "\n";
    std::cout << "S1 inside C1? " << (square_inside_circle_strict(s1, c1) ? "YES" : "NO") << "\n";
    std::cout << "C1 inside S1? " << (circle_inside_square_strict(c1, s1) ? "YES" : "NO") << "\n";

    std::cout << "\nDone.\n";
    return 0;
}
