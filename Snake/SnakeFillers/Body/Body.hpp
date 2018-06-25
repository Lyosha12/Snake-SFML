//
// Created by Lyosha12 on 24.06.2018.
//

#ifndef SNAKE_BODY_HPP
#define SNAKE_BODY_HPP

#include <functional>
#include "../../../Utilites/Coord/Coord.hpp"
#include "../../../Utilites/TextureStorage/TextureStorage.hpp"
#include "../../../BonusManager/SteppedOnBody/SteppedOnBody.hpp"
#include "../../../CellsPool/Cell/Filler/Filler.hpp"

class DefaultRectangle;
class Bonus;
class Snake;

class Body: public Filler {
  public:
    Body(DefaultRectangle const& default_rectangle, Coord const& coord,
         std::function<std::unique_ptr<Bonus>(Snake&)> bonus_creator);
    
    using BonusType = SteppedOnBody;
  
  private:
    inline static TextureStorage texture {
        TextureStorage::LoadTextureParams{"Body.png", false}
    };
};


#endif //SNAKE_BODY_HPP
