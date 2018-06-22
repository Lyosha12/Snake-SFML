//
// Created by Lyosha12 on 18.06.2018.
//

#ifndef SNAKE_CELL_HPP
#define SNAKE_CELL_HPP

#include <SFML/Graphics.hpp>

#include "../../Coord/Coord.hpp"
// #include "../RequestedCell/RequestedCell.hpp"

// #include "../Snake/Snake.hpp"
class Snake;
class RequestedCell;

class Cell: public sf::Drawable {
    // Представляет клетку на поле.
    // Клетка имеет координаты, возможность
    // быть использованной(usable) или нет.
    // Имеет заполнитель - то, чем она является.
    // Заполнитель контролирует бассейн клеток (cells_pool).
    
  public:
    class Filler: public sf::Drawable {
      // Заполнитель клетки - это некий спрайт.
      // Его текстуру и форму определяет наследник этого класса.
    
      // Каждую клетку змейка может занять.
      // И, в зависимости от реализации функции modify,
      // змейка будет изменена так или иначе.
      
      // Так как заполнитель может быть пуст, то вызывать modify нельзя.
      // Это контролирует вспомогательный класс RequestedCell.
        friend RequestedCell;
        
      public:
        Filler(sf::Sprite sprite);
        virtual ~Filler() = default;
        
      private:
        virtual void modify(Snake&) const;
        sf::Sprite sprite;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
  
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
    bool is_usable = true; // Изначально змейка может попасть в любую клетку.
    
  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif //SNAKE_CELL_HPP
