//
// Created by Lyosha12 on 22.06.2018.
//

#ifndef SNAKE_DEFAULTRECTANGLE_HPP
#define SNAKE_DEFAULTRECTANGLE_HPP

#include <SFML/Graphics.hpp>
#include "Utility/Coord/Coord.hpp"

class DefaultRectangle {
    // Стандартный прямоугольник поля.
    // В процессе игры он переиспользуется для
    // определения размеров других клеток и установки их координат,
    // исходя из их положения в массиве координат (бассейне клеток).
  
  public:
    DefaultRectangle(sf::Vector2u const& size);
    
    sf::Sprite makeSprite(sf::Texture const& texture, Coord on_field, double rotation) const;
    sf::Vector2f getSize() const;
  
  private:
    sf::RectangleShape prototype;
};

#endif //SNAKE_DEFAULTRECTANGLE_HPP
