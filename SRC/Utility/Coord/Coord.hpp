//
// Created by Lyosha12 on 18.06.2018.
//

#ifndef SNAKE_COORD_HPP
#define SNAKE_COORD_HPP

#include <cmath>

struct Coord {
    // Описывает координату прямоугольника на игровом поле.
    // От левого верхнего угла: i - по ширине, y - по высоте.
    // Координаты целые знаковые - это позволяет использовать
    // их как компоненты вектора направления змейки или другого объекта.
    int x = -1, y = -1;
    Coord() = default;
    Coord(int x, int y);
    Coord(size_t x, size_t y);
    
    friend int    pseudoscalar (Coord const& L, Coord const& R);
    friend bool   isCollinear  (Coord const& L, Coord const& R);
    friend int    scalar       (Coord const& L, Coord const& R);
    friend double angle        (Coord const& L, Coord const& R);
    
    double length    (                ) const;
    bool   operator==(double value    ) const;
    Coord operator*  (int value       ) const;
    
    bool  operator== (Coord const& rhs) const;
    bool  operator!= (int value       ) const;
    Coord operator+  (Coord const& rhs) const;
    Coord operator-  (Coord const& rhs) const;
    Coord operator-  (                ) const;
    
    
    Coord operator*= (int value       );
};


#endif //SNAKE_COORD_HPP
