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
    Coord(int x, int y);
    Coord(size_t x, size_t y);
    
    
    double vectorLength() const;
    
    bool  operator== (double value) const;
    bool  operator== (Coord const& rhs) const;
    bool  operator!= (int value) const;
    Coord operator+  (Coord const& rhs) const;
    Coord operator-  (Coord const& rhs) const;
    Coord operator-  () const;
};


#endif //SNAKE_COORD_HPP
