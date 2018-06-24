//
// Created by Lyosha12 on 24.06.2018.
//

#include "FreeCellFiller.hpp"

FreeCellFiller::FreeCellFiller(
    DefaultRectangle const& default_rectangle,
    Coord const& coord
) : Filler(default_rectangle, coord, sf::Texture(), true)
{ }

void FreeCellFiller::modify(Snake& snake) const {
    // Змейка не может быть нулевой длины.
    snake.popBodyChapter(snake.bodyLength() - 1);
}