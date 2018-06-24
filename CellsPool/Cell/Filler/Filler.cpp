//
// Created by Lyosha12 on 22.06.2018.
//

#include "Filler.hpp"
void endGame() {
    exit(0xE8D);
}

Filler::Filler(
    DefaultRectangle const& default_rectangle,
    Coord const& coord,
    sf::Texture const& texture,
    bool is_free
): is_free(is_free)
{
    this->sprite = default_rectangle.configure(
        DefaultRectangle::Configurator(coord, texture)
    );
    
    // Позволяет узнать во сколько раз нужно уменьшить
    // текстуру по отношению к размеру клетки.
    sf::Vector2f scale = {
        default_rectangle.getSize().x / texture.getSize().x,
        default_rectangle.getSize().y / texture.getSize().y
    };
    
    this->sprite.setScale(scale);
}

void Filler::modify(Snake&) const { }

void Filler::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

bool Filler::isFree() const {
    return is_free;
}