// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 22.06.2018.
//

#include "NotFoundFreeCell.hpp"

NotFoundFreeCell::NotFoundFreeCell(Cell::CellCPtr cell, std::string explanation)
: cell(cell)
, explanation(explanation)
{ }

char const* NotFoundFreeCell::what() const noexcept {
    std::string reason = "Free cell not found. Params:\n";
    reason +=
        "  - Cell coord: (" +
        std::to_string(cell->coord.x) + ", " +
        std::to_string(cell->coord.y) + ").\n";
    
    explanation = reason += "  - Other info: " + explanation + "\n";
    
    return explanation.c_str();
}