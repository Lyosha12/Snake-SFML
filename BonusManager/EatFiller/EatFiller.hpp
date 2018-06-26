//
// Created by Lyosha12 on 26.06.2018.
//

#ifndef SNAKE_EATFILLER_HPP
#define SNAKE_EATFILLER_HPP

#include <functional>
#include "../../Utilites/TextureStorage/TextureStorage.hpp"
#include "../../Utilites/Coord/Coord.hpp"
#include "../../BonusManager/SteppedOnHead/SteppedOnHead.hpp"
#include "../../CellsPool/Cell/Filler/Filler.hpp"
#include "../Eat/Eat.hpp"

class DefaultRectangle;
class Bonus;
class Snake;

class EatFiller: public Filler {
  public:
    EatFiller(DefaultRectangle const& default_rectangle, Coord const& coord,
         std::function<std::unique_ptr<Bonus>(Snake&)> bonus_creator);
    
    using BonusType = Eat;
  
  private:
    inline static TextureStorage texture {
        TextureStorage::LoadTextureParams{"Eat.png", false}
    };
};


#endif //SNAKE_EATFILLER_HPP
