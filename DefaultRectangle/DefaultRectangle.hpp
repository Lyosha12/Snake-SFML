//
// Created by Lyosha12 on 18.06.2018.
//

#ifndef SNAKE_DEFAULTRECTANGLE_HPP
#define SNAKE_DEFAULTRECTANGLE_HPP

#include <SFML/Graphics.hpp>
#include "../Coord/Coord.hpp"

class DefaultRectangle {
    // Стандартный прямоугольник поля.
    // В процессе игры он переиспользуется для
    // определения размеров других клеток и установки их координат,
    // исходя из их положения в массиве координат (бассейне клеток).
  
  public:
    DefaultRectangle(float cell_width, float cell_height);
    
    class Configurator {
        // У любого прямоугольника поля есть позиция,
        // цвет и масштаб относительно других прямоугольников.
        // Класс определяет на поле конкретный прямоугольник из стандартного.
        
      public:
        Configurator(Coord pos_on_field, sf::Texture const& texture);
      
      private:
        friend class DefaultRectangle;
        
        sf::Sprite operator() (sf::RectangleShape const&) const;
        void setPos(sf::Sprite& sprite, sf::RectangleShape const&) const;
      
      private:
        Coord pos_on_field;
        sf::Texture const& texture;
    };
    
    sf::Sprite configure(Configurator const& configurator) const;
    sf::Vector2f getSize() const;
    
  private:
    sf::RectangleShape default_rectangle;
};


#endif //SNAKE_DEFAULTRECTANGLE_HPP
