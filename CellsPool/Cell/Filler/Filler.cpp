//
// Created by Lyosha12 on 22.06.2018.
//

#include "Filler.hpp"

#include "../../../Utilites/Coord/Coord.hpp"
#include "../../DefaultRectangle/DefaultRectangle.hpp"

Filler::Filler(
    DefaultRectangle const& default_rectangle,
    Coord const& coord,
    sf::Texture const& texture,
    CanBeTake can_be_take,
    Bonus::LazyCreator const& bonus_creator,
    Bonus::LazyDestroyer const& bonus_destroy_notify
)
    : can_be_take(can_be_take)
    , bonus_creator(bonus_creator)
    , bonus_destroy_notify(bonus_destroy_notify)
{
    // Установим переданную текстуру в спрайт, настроив её размер.
    this->sprite = default_rectangle.configureTexture(
        DefaultRectangle::TextureConfigurator(coord, texture)
    );
    
    // Позволяет узнать во сколько раз нужно уменьшить
    // текстуру по отношению к размеру клетки.
    sf::Vector2f scale = {
        default_rectangle.getSize().x / texture.getSize().x,
        default_rectangle.getSize().y / texture.getSize().y
    };
    
    this->sprite.setScale(scale);
}

Filler::~Filler() {
    bonus_destroy_notify();
}

std::unique_ptr<Bonus> Filler::getBonus(Snake& snake) const {
    return std::move(bonus_creator(snake));
}

void Filler::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

bool Filler::isCanBeTake() const {
    return can_be_take == CanBeTake::Yes;
}