//
// Created by Lyosha12 on 26.06.2018.
//

#ifndef SNAKE_EATFILLER_HPP
#define SNAKE_EATFILLER_HPP

#include <functional>
#include "../../../Utilites/TextureStorage/TextureStorage.hpp"
#include "../../../Utilites/Coord/Coord.hpp"
#include "../../../BonusManager/SteppedOnHead/SteppedOnHead.hpp"
#include "../Filler/Filler.hpp"
#include "../../../BonusManager/Eat/Eat.hpp"

class DefaultRectangle;
class Bonus;
class Snake;

class EatFiller: public Filler {
  public:
    template <class BonusType = Eat>
    EatFiller(DefaultRectangle const& default_rectangle, Coord const& coord)
    : Filler(
          default_rectangle, coord, texture, CanBeTake::Yes,
          BonusType::getBonusCreator(), BonusType::getBonusDestroyer()
      )
    { }
    
  
  private:
    inline static TextureStorage texture {
        TextureStorage::LoadTextureParams{"Eat.png", false}
    };
};


#endif //SNAKE_EATFILLER_HPP
