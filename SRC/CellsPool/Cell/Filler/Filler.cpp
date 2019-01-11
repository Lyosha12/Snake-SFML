// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
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
    // Бонус получен -> бонуса нет на поле.
    // bonus_creator сообщит об этом менеджеру бонусов
    // и создаст бонус, привязав этот бонус к змейке.
    return std::move(bonus_creator(snake));
}

void Filler::draw(sf::RenderTarget& target, sf::RenderStates states) const { //-V813
    target.draw(sprite, states);
}

bool Filler::isCanBeTake() const {
    return can_be_take == CanBeTake::Yes;
}