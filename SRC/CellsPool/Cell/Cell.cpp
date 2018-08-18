// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 18.06.2018.
//

#include "Cell.hpp"
#include "Filler/Filler.hpp"

Cell::Cell(Cell&& cell)
    : coord(cell.coord)
    , filler(std::move(cell.filler))
{ }

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const { //-V813
    if(filler)
        target.draw(*filler, states);
}