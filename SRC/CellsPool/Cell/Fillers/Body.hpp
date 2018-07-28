//
// Created by Lyosha12 on 24.06.2018.
//

#ifndef SNAKE_BODY_HPP
#define SNAKE_BODY_HPP

#include <functional>
#include "BonusManager/SteppedOnBody/SteppedOnBody.hpp"
#include "CellsPool/Cell/Filler/Filler.hpp"

class DefaultRectangle;
class Bonus;
class Snake;

class Body: public Filler {
  public:
    template <class BonusType = SteppedOnBody>
    Body(DefaultRectangle const& default_rectangle, Coord const& coord)
    : Filler(
          default_rectangle, coord, texture,
          BonusType::getBonusCreator(),
          BonusType::getBonusDestroyer(),
          CanBeTake::No
      )
    { }
    
  
  private:
    inline static TextureStorage texture {
        TextureStorage::TextureParams{"Body.png", false}
    };
};


#endif //SNAKE_BODY_HPP
