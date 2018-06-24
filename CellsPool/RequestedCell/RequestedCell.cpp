//
// Created by Lyosha12 on 22.06.2018.
//

#include "RequestedCell.hpp"

RequestedCell::
RequestedCell(Cell const* cell, std::unique_ptr<Filler> prev_filler)
: prev_filler(std::move(prev_filler))
, cell(cell)
{ }

void RequestedCell::modify (Snake& snake) const {
    if(prev_filler)
        prev_filler->modify(snake);
}