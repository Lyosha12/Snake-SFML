//
// Created by Lyosha12 on 18.06.2018.
//

#ifndef SNAKE_CELL_HPP
#define SNAKE_CELL_HPP

#include <SFML/Graphics.hpp>
#include "Utility/Coord/Coord.hpp"
#include "Filler/Filler.hpp"


class Snake;

class Cell: public sf::Drawable {
    // Представляет клетку на поле.
    // Клетка содержит заполнитель (filler).
    // Filler - это еда, препятствие, блок змейки и т.д.
    // Какой заполнитель установить и как решает бассейн клеток (CellsPool).
  
  public:
    using FillerUPtr = Filler::FUP;
    using CellCPtr   = Cell const*;
    using CellPtr    = Cell*;
    
  public:
    Cell() = default;
    Cell(Cell&& cell);
    Cell(Cell const&) = delete;
    
    Coord coord = {-1, -1};
    std::unique_ptr<Filler> filler = nullptr;
    
  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif //SNAKE_CELL_HPP
