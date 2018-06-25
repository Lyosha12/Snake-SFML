//
// Created by Lyosha12 on 24.06.2018.
//

#ifndef SNAKE_BODY_HPP
#define SNAKE_BODY_HPP

#include "../../../CellsPool/Cell/Filler/Filler.hpp"
#include "../../../TextureStorage/TextureStorage.hpp"
#include "../../../BonusManager/SteppedOnBody/SteppedOnBody.hpp"

class Body: public Filler {
  public:
    Body(DefaultRectangle const& default_rectangle, Coord const& coord,
         std::function<std::unique_ptr<Bonus>(Snake&)> bonus_creator);
  
  private:
    inline static TextureStorage texture {
        TextureStorage::LoadTextureParams{"Body.png", false}
    };
    
    using BonusType = SteppedOnBody;
};


#endif //SNAKE_BODY_HPP
