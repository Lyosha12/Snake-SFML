//
// Created by Lyosha12 on 22.06.2018.
//

#include "Cell.hpp"

Cell::Filler::Filler(sf::Sprite sprite) : sprite(sprite) { }

void Cell::Filler::modify(Snake&) const { }

void Cell::Filler::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}