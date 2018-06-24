//
// Created by Lyosha12 on 18.06.2018.
//

#ifndef SNAKE_CELL_HPP
#define SNAKE_CELL_HPP

#include <SFML/Graphics.hpp>

#include "../../Coord/Coord.hpp"
#include "Filler/Filler.hpp"

class Snake;
class Cell: public sf::Drawable {
    // Представляет клетку на поле.
    // Имеет заполнитель - то, чем она является для змейки.
    // Заполнитель контролирует бассейн клеток (cells_pool).
  
  public:
    using FillerUPtr = std::unique_ptr<Filler>;
    using CellCPtr   = Cell const*;
    using CellPtr    = Cell*;
    
  public:
    Cell() = default;
    Cell(Cell&& cell);
    
    Coord coord = {-1, -1};
    // Задаётся в конструкторе бассейна клеток,
    // Т.к. только бассейну известна координата клетки и её размер,
    // чтобы разместить там спрайт.
    std::unique_ptr<Filler> filler = nullptr;
    
  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif //SNAKE_CELL_HPP
