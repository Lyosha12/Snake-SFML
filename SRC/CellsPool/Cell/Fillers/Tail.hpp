//
// Created by Lyosha12 on 24.06.2018.
//

#ifndef SNAKE_TAIL_HPP
#define SNAKE_TAIL_HPP

#include "BonusManager/SteppedOnBody/SteppedOnBody.hpp"
#include "CellsPool/Cell/Filler/Filler.hpp"

class Tail: public Filler {
  public:
    template <class BonusType = SteppedOnBody>
    Tail(SpriteMaker sprite_maker)
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
        TextureStorage::TextureParams{"Tail.png", false}
    };
};


#endif //SNAKE_TAIL_HPP
