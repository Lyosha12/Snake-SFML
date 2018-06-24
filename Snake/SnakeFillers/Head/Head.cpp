//
// Created by Lyosha12 on 24.06.2018.
//

#include "Head.hpp"

Head::Head(DefaultRectangle const& default_rectangle, Coord const& coord)
    : Filler(default_rectangle, coord, texture)
{ }

void Head::modify(Snake& snake) const {
    endGame();
}