//
// Created by Lyosha12 on 24.06.2018.
//

#ifndef SNAKE_BODYANGLE_HPP
#define SNAKE_BODYANGLE_HPP

#include "BonusManager/SteppedOnBody/SteppedOnBody.hpp"
#include "CellsPool/Cell/Filler/Filler.hpp"

class BodyAngle: public Filler {
  public:
    template <class BonusType = SteppedOnBody>
    BodyAngle(SpriteMaker sprite_maker)
    : Filler(
          sprite_maker(texture),
          BonusType::getBonusCreator(),
          BonusType::getBonusDestroyer(),
          CanBeTake::No
      )
    { }
    
    inline static const Coord orientation = {1, 1};
  
  private:
    inline static TextureStorage texture {
        TextureStorage::TextureParams{"BodyAngle.png", false}
    };
};


#endif //SNAKE_BODYANGLE_HPP
