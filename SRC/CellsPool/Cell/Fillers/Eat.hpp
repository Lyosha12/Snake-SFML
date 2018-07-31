//
// Created by Lyosha12 on 26.06.2018.
//

#ifndef SNAKE_EATFILLER_HPP
#define SNAKE_EATFILLER_HPP

#include <functional>
#include "CellsPool/Cell/Filler/Filler.hpp"
#include "BonusManager/AddChapter/AddChapter.hpp"

class DefaultRectangle;
class Bonus;
class Snake;

class Eat: public Filler {
  public:
    template <class BonusType = AddChapter>
    Eat(DefaultRectangle const& default_rectangle, Coord const& coord)
    : Filler(
          default_rectangle, coord, texture,
          BonusType::getBonusCreator(),
          BonusType::getBonusDestroyer(),
          CanBeTake::Yes
      )
    { }
    
  
  private:
    inline static TextureStorage texture {
        TextureStorage::TextureParams{"Eat.png", false}
    };
};


#endif //SNAKE_EATFILLER_HPP
