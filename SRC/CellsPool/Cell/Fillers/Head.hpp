//
// Created by Lyosha12 on 24.06.2018.
//

#ifndef SNAKE_HEAD_HPP
#define SNAKE_HEAD_HPP

#include "BonusManager/SteppedOnHead/SteppedOnHead.hpp"
#include "CellsPool/Cell/Filler/Filler.hpp"

class Head: public Filler {
  public:
    template <class BonusType = SteppedOnHead>
    Head(SpriteMaker sprite_maker)
    : Filler(
        sprite_maker(texture),
        BonusType::getBonusCreator(),
        BonusType::getBonusDestroyer(),
        CanBeTake::No
      )
    { }
    
    inline static const Coord orientation = {1, 0};
    
  private:
    inline static TextureStorage texture {
        TextureStorage::TextureParams{"Head.png", false}
    };
};


#endif //SNAKE_HEAD_HPP
