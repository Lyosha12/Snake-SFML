//
// Created by Lyosha12 on 18.06.2018.
//

#include "DefaultRectangle.hpp"

DefaultRectangle::DefaultRectangle(float cell_width, float cell_height)
    : default_rectangle({cell_width, cell_height})
{ }

sf::Sprite DefaultRectangle::configure(Configurator const& configurator) const {
    // Создание по указанным настройкам прямоугольника для игрового поля.
    return configurator(default_rectangle);
}





DefaultRectangle::Configurator::Configurator(Coord pos_on_field, sf::Texture const& texture)
: pos_on_field(pos_on_field)
, texture(texture)
{ }

sf::Sprite DefaultRectangle::Configurator::
operator() (sf::RectangleShape const& default_rectangle) const {
    sf::Sprite sprite(texture);
    setPos(sprite, default_rectangle);
    
    return sprite;
}

void DefaultRectangle::Configurator::
setPos(sf::Sprite& sprite, sf::RectangleShape const& default_rectangle) const {
    // В соответствии с текущими настройками
    // устанавливается позиция для переданного прямоугольника.
    float width  = default_rectangle.getSize().x;
    float height = default_rectangle.getSize().y;
    sprite.setPosition(width * pos_on_field.x, height * pos_on_field.y);
}