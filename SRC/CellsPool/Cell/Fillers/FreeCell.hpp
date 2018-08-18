//
// Created by Lyosha12 on 24.06.2018.
//

#ifndef SNAKE_FREECELLFILLER_HPP
#define SNAKE_FREECELLFILLER_HPP

#include "CellsPool/Cell/Filler/Filler.hpp"
#include "BonusManager/Move/Move.hpp"

class FreeCell: public Filler {
    // * Заполнитель по-умолчанию. Это клетка,
    //   доступная к перемещению на неё.
    // * Текстуру поля в одну клетку не засунешь - в пустой клетке отсутствует.
    //   Текстура свободного поля определяется бассейном клеток.
    
  public:
    template <class BonusType = Move>
    FreeCell(SpriteMaker sprite_maker)
    : Filler(
        sprite_maker(sf::Texture() /* Пустая */),
        BonusType::getBonusCreator(),
        BonusType::getBonusDestroyer(),
        CanBeTake::Yes
      )
    { }
    
    inline static const Coord orientation = {0, 0}; // Свободная клетка не ориентирована ни в какую сторону.
};


#endif //SNAKE_FREECELLFILLER_HPP
