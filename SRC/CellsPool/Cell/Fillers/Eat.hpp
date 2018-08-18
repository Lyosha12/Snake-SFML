//
// Created by Lyosha12 on 26.06.2018.
//

#ifndef SNAKE_EATFILLER_HPP
#define SNAKE_EATFILLER_HPP

#include "CellsPool/Cell/Filler/Filler.hpp"
#include "BonusManager/AddChapter/AddChapter.hpp"

class Eat: public Filler {
  public:
    template <class BonusType = AddChapter>
    Eat(SpriteMaker sprite_maker)
    : Filler(
        sprite_maker(texture),
        BonusType::getBonusCreator(),
        BonusType::getBonusDestroyer(),
        CanBeTake::Yes
      )
    { }
    
    inline static const Coord orientation = {-1, 0}; // Ориентация еды не используется (пока?).
  
  private:
    inline static TextureStorage texture {
        TextureStorage::TextureParams{"Eat.png", false}
    };
};


#endif //SNAKE_EATFILLER_HPP
