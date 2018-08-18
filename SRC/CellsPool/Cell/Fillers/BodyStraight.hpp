//
// Created by Lyosha12 on 24.06.2018.
//

#ifndef SNAKE_BODYSTRAIGHT_HPP
#define SNAKE_BODYSTRAIGHT_HPP

#include "BonusManager/SteppedOnBody/SteppedOnBody.hpp"
#include "CellsPool/Cell/Filler/Filler.hpp"

class BodyStraight: public Filler {
  public:
    template <class BonusType = SteppedOnBody>
    BodyStraight(SpriteMaker sprite_maker)
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
        TextureStorage::TextureParams{"BodyStraight.png", false}
    };
};


#endif //SNAKE_BODYSTRAIGHT_HPP
