//
// Created by Lyosha12 on 25.06.2018.
//

#include "Snake/GameEnd.hpp"
#include "SteppedOnHead.hpp"

bool SteppedOnHead::activate() {
    throw GameEnd("Game is end");
}

Bonus::LazyCreator const& SteppedOnHead::getBonusCreator() {
    return lazy_creator;
}

Bonus::LazyDestroyer const& SteppedOnHead::getBonusDestroyer() {
    return bonus_destroy_notify;
}

const Bonus::LazyCreator SteppedOnHead::lazy_creator = [] (Snake& snake) {
    return std::unique_ptr<Bonus>(new SteppedOnHead(snake));
};

const Bonus::LazyDestroyer SteppedOnHead::bonus_destroy_notify = [] {
    // Тут тоже делать нечего.
    // Никому не интересно, что часть тела уничтожена,
    // кроме самой змейки.
};