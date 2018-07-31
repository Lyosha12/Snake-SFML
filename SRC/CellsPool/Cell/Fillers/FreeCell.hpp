//
// Created by Lyosha12 on 24.06.2018.
//

#ifndef SNAKE_FREECELLFILLER_HPP
#define SNAKE_FREECELLFILLER_HPP

#include "CellsPool/Cell/Filler/Filler.hpp"
#include "BonusManager/Move/Move.hpp"

class Snake;

class FreeCell: public Filler {
    // * Заполнитель по-умолчанию. Это клетка,
    //   доступная к перемещению на неё.
    // * Текстуру поля в одну клетку не засунешь - в пустой клетке отсутствует.
    //   Текстура свободного поля определяется бассейном клеток.
    
  public:
    template <class BonusType = Move>
    FreeCell(
        DefaultRectangle const& default_rectangle, Coord const& coord
    ): Filler(
        default_rectangle, coord, sf::Texture() /* Пустая */,
        BonusType::getBonusCreator(),
        BonusType::getBonusDestroyer(),
        CanBeTake::Yes
       )
    { }
};


#endif //SNAKE_FREECELLFILLER_HPP
