//
// Created by Lyosha12 on 18.06.2018.
//

#include "Cell.hpp"
#include "Filler/Filler.hpp"

Cell::Cell(Cell&& cell)
    : coord(cell.coord)
    , filler(std::move(cell.filler))
{ }

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(filler)
        target.draw(*filler, states);
}