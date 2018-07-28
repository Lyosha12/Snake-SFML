//
// Created by Lyosha12 on 22.06.2018.
//

#ifndef SNAKE_NOTFOUNDFREECELL_HPP
#define SNAKE_NOTFOUNDFREECELL_HPP

#include <string>
#include <exception>
#include "CellsPool/Cell/Cell.hpp"


struct NotFoundFreeCell: public std::exception {
    NotFoundFreeCell(Cell::CellCPtr cell, std::string explanation = "not present");
    
    char const* what() const noexcept override;
    
    Cell::CellCPtr cell;
    std::string explanation;
};


#endif //SNAKE_NOTFOUNDFREECELL_HPP
