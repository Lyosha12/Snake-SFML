//
// Created by Lyosha12 on 24.06.2018.
//

#ifndef SNAKE_HEAD_HPP
#define SNAKE_HEAD_HPP

#include <functional>
#include "../../../Utilites/TextureStorage/TextureStorage.hpp"
#include "../../../Utilites/Coord/Coord.hpp"
#include "../../../BonusManager/SteppedOnHead/SteppedOnHead.hpp"
#include "../Filler/Filler.hpp"

class DefaultRectangle;
class Bonus;
class Snake;

class Head: public Filler {
  public:
    template <class BonusType = SteppedOnHead>
    Head(DefaultRectangle const& default_rectangle, Coord const& coord)
    : Filler(
        default_rectangle, coord, texture,
        BonusType::getBonusCreator(),
        BonusType::getBonusDestroyer(),
        CanBeTake::No
    )
    { }
    
    using BonusType = SteppedOnHead;
    
  private:
    inline static TextureStorage texture {
        TextureStorage::LoadTextureParams{"Head.png", false}
    };
};


#endif //SNAKE_HEAD_HPP
