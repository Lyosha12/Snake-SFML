//
// Created by Lyosha12 on 18.06.2018.
//

#include "Coord.hpp"

Coord::Coord(int x, int y): x(x), y(y) { }
Coord::Coord(size_t x, size_t y): x(x), y(y) { }


double Coord::vectorLength() const {
    return std::sqrt(x*x + y*y);
}

bool  Coord::operator== (double value) const {
    return std::abs(vectorLength() - value) < 1e-5;
}

bool  Coord::operator== (Coord const& rhs) {
    return this->x == rhs.x && this->y == rhs.y;
}

bool  Coord::operator!= (int value) const {
    return !(*this == value);
}

Coord Coord::operator+  (Coord const& rhs) const {
    return {this->x + rhs.x, this->y + rhs.y};
}

Coord Coord::operator-  (Coord const& rhs) const {
    return *this + -rhs;
}

Coord Coord::operator-  () const {
    return {-this->x, -this->y};
}