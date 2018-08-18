//
// Created by Lyosha12 on 22.06.2018.
//

#include "Filler.hpp"
#include "Utility/WindowForTests/WindowForTests.hpp"

Filler::Filler(
    sf::Sprite sprite,
    Bonus::LazyCreator const& bonus_creator,
    Bonus::LazyDestroyer const& bonus_destroy_notify,
    CanBeTake can_be_take
)
    : sprite(sprite)
    , bonus_creator(bonus_creator)
    , bonus_destroy_notify(bonus_destroy_notify)
    , can_be_take(can_be_take)
{ }

Filler::~Filler() {
    bonus_destroy_notify();
}

std::unique_ptr<Bonus> Filler::getBonus(Snake& snake) const {
    // Бонус получе - бонуса нет на поле.
    // bonus_creator сообщит об этом и создаст бонус с привязкой к змейке.
    return std::move(bonus_creator(snake));
}

void Filler::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

bool Filler::isCanBeTake() const {
    return can_be_take == CanBeTake::Yes;
}