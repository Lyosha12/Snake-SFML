//
// Created by Lyosha12 on 22.06.2018.
//

#include "Filler.hpp"

#include "../../../Utilites/Coord/Coord.hpp"
#include "../../DefaultRectangle/DefaultRectangle.hpp"
#include "../../../BonusManager/Bonus/Bonus.hpp"

Filler::Filler(
    DefaultRectangle const& default_rectangle,
    Coord const& coord,
    sf::Texture const& texture,
    bool is_free,
    std::function<std::unique_ptr<Bonus>(Snake&)> bonus_creator
): is_free(is_free), bonus_creator(std::move(bonus_creator))
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

std::unique_ptr<Bonus> Filler::getBonus(Snake& snake) const {
    return std::move(bonus_creator(snake));
}

void Filler::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

bool Filler::isFree() const {
    return is_free;
}