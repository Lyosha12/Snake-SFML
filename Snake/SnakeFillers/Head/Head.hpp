//
// Created by Lyosha12 on 24.06.2018.
//

#ifndef SNAKE_HEAD_HPP
#define SNAKE_HEAD_HPP

#include "../../../CellsPool/Cell/Filler/Filler.hpp"
#include "../../../TextureStorage/TextureStorage.hpp"

class Head: public Filler {
  public:
    Head(DefaultRectangle const& default_rectangle, Coord const& coord);
    void modify(Snake& snake) const override;
  
  private:
    inline static TextureStorage texture {
        TextureStorage::LoadTextureParams{"Head.png", false}
    };
};


#endif //SNAKE_HEAD_HPP
