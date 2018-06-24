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
    // Заполнитель для клетки по-умолчанию отсутствует.
    // Текстуру поля в одну клетку не засунешь. Поэтому
    // текстура поля рассредоточена по нескольким клеткам
    // бесшовной повторяющейся текстурой.
    std::unique_ptr<Filler> filler = nullptr;
    
  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif //SNAKE_CELL_HPP
