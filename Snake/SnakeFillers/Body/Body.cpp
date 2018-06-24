//
// Created by Lyosha12 on 24.06.2018.
//

#include "Body.hpp"

Body::Body(DefaultRectangle const& default_rectangle, Coord const& coord)
    : Filler(default_rectangle, coord, texture)
{ }

void Body::modify(Snake& snake) const {
    endGame();
}