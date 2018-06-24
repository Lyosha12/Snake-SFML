//
// Created by Lyosha12 on 22.06.2018.
//

#include "Filler.hpp"

Filler::Filler(
    DefaultRectangle const& default_rectangle,
    Coord const& coord,
    sf::Texture const& texture,
    bool is_usable
): is_usable(is_usable)
{
    this->sprite = default_rectangle.configure(
        DefaultRectangle::Configurator(coord, texture)
    );
    
    sf::Vector2f scale = {
        default_rectangle.getSize().x / texture.getSize().x,
        default_rectangle.getSize().y / texture.getSize().y
    };
    
    this->sprite.setScale(scale);
}

void Filler::modify(Snake&) const { }

bool Filler::isUsable() const {
    return is_usable;
}

void Filler::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

