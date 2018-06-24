//
// Created by Lyosha12 on 24.06.2018.
//

#ifndef SNAKE_BODY_HPP
#define SNAKE_BODY_HPP

#include "../../../CellsPool/Cell/Filler/Filler.hpp"
#include "../../../TextureStorage/TextureStorage.hpp"

class Body: public Filler {
  public:
    Body(DefaultRectangle const& default_rectangle, Coord const& coord);
    void modify(Snake& snake) const override;
  
  private:
    inline static TextureStorage texture {
        TextureStorage::LoadTextureParams{"Body.png", false}
    };
};


#endif //SNAKE_BODY_HPP
