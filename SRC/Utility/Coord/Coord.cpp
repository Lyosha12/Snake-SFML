//
// Created by Lyosha12 on 18.06.2018.
//

#include "Coord.hpp"

Coord::Coord(int x, int y): x(x), y(y) { }
Coord::Coord(size_t x, size_t y): x(x), y(y) { }

int    pseudoscalar  (Coord const& L, Coord const& R) {
    return L.x*R.y - L.y*R.x;
}
bool   isCollinear   (Coord const& L, Coord const& R) {
    return std::abs(pseudoscalar(L, R)) <= 1e-5;
}
int    scalar        (Coord const& L, Coord const& R) {
    return L.x*R.x + L.y*R.y;
}
double angle         (Coord const& L, Coord const& R) {
    double cos = scalar(L, R) / (L.length() * R.length());
    double angle = acos(cos) * 180/M_PI;
    
    if((pseudoscalar(L, R) <= 0)) {
        angle = (360 - angle);
    }
    
    return angle; // Угол поворота против часовой стрелки.
}

double Coord::length (                              ) const {
    return std::sqrt(scalar(*this, *this));
}
bool  Coord::operator== (double value    ) const {
    return std::abs(length() - value) < 1e-5;
}
bool  Coord::operator== (Coord const& rhs) const {
    return this->x == rhs.x && this->y == rhs.y;
}
bool  Coord::operator!= (int value       ) const {
    return !(*this == value);
}

Coord Coord::operator*  (int value       ) const {
    return Coord (this->x * value, this->y * value);
}
Coord Coord::operator+  (Coord const& rhs) const {
    return {this->x + rhs.x, this->y + rhs.y};
}
Coord Coord::operator-  (Coord const& rhs) const {
    return *this + -rhs;
}
Coord Coord::operator-  (                ) const {
    return {-this->x, -this->y};
}



Coord Coord::operator*= (int value       )       {
    return *this = *this * value;
}
