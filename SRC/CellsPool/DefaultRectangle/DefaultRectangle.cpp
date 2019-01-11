// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 18.06.2018.
//

#include "Utility/WindowForTests/WindowForTests.hpp"
#include "DefaultRectangle.hpp"

DefaultRectangle::DefaultRectangle(sf::Vector2u const& size)
    : prototype({static_cast<float>(size.x), static_cast<float>(size.y)})
{ }

sf::Sprite DefaultRectangle::
makeSprite(sf::Texture const& texture, Coord on_field, double rotation) const {
    sf::Sprite sprite(texture);

    // Узнаем коэффициенты масштабов спрайта, чтобы он влез в прямоугольник.
    sf::Vector2f scale = {
        prototype.getSize().x / texture.getSize().x,
        prototype.getSize().y / texture.getSize().y
    };
    sprite.setScale(scale);
    
    // Повернём относительно центра.
    sf::Vector2f origin = {
        sprite.getTextureRect().width / 2.0f,
        sprite.getTextureRect().height / 2.0f
    };
    sprite.setOrigin(origin);
    // Т.к. угол поворота получен как против часовой стрелки,
    // а функция вращения работает по часовой - инвертируем.
    sprite.rotate(static_cast<float>(-rotation));
    
    // Установим нужную позицию на поле для спрайта.
    sf::Vector2f const& default_size = prototype.getSize();
    float width  = default_size.x;
    float height = default_size.y;
    sf::Vector2f magic_offset = {
        width /2  - width/5,
        height/2 - height/5
    };
    sprite.setPosition(width * on_field.x + origin.x, height * on_field.y + origin.y);
    sprite.move(magic_offset);
    
    return sprite;
}

sf::Vector2f DefaultRectangle::getSize() const {
    return prototype.getSize();
}


