//
// Created by Lyosha12 on 18.06.2018.
//

#ifndef SNAKE_COORD_HPP
#define SNAKE_COORD_HPP

#include <cmath>

struct Coord {
    // Описывает координату прямоугольника на игровом поле.
    // От левого верхнего угла: x - по ширине, y - по высоте.
    // Координаты целые знаковые - это позволяет использовать
    // их как компоненты вектора направления змейки или другого объекта.
    int x = -1, y = -1;
    Coord(int x, int y): x(x), y(y) { }
    Coord(size_t x, size_t y): x(x), y(y) { }
    
    
    double vectorLength() const {
        return std::sqrt(x*x + y*y);
    }
    
    bool  operator== (double value) const {
        return std::abs(vectorLength() - value) < 1e-5;
    }
    bool  operator== (Coord const& rhs) {
        return this->x == rhs.x && this->y == rhs.y;
    }
    bool  operator!= (int value) const {
        return !(*this == value);
    }
    Coord operator+  (Coord const& rhs) const {
        return {this->x + rhs.x, this->y + rhs.y};
    }
    Coord operator-  (Coord const& rhs) const {
        return *this + -rhs;
    }
    Coord operator-  () const {
        return {-this->x, -this->y};
    }
};


#endif //SNAKE_COORD_HPP
