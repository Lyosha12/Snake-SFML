//
// Created by Lyosha12 on 22.06.2018.
//

#include "NotFoundFreeCell.hpp"

NotFoundFreeCell::NotFoundFreeCell(Cell&& cell, std::string explanation)
: cell(cell)
, explanation(explanation)
{ }

char const* NotFoundFreeCell::what() const noexcept {
    std::string reason = "Free cell not found. Params:\n";
    reason +=
        "  - Coords cell: (" +
        std::to_string(cell.coord.x) + ", " +
        std::to_string(cell.coord.y) + ").\n";
    
    reason += "  - Other info: " + explanation + "\n";
    
    return reason.c_str();
}