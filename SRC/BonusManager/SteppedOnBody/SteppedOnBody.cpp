// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 25.06.2018.
//

#include "Snake/EndGame.hpp"
#include "SteppedOnBody.hpp"

bool SteppedOnBody::activate() {
    throw EndGame("Game is end");
}

Bonus::LazyCreator const& SteppedOnBody::getBonusCreator() {
    return lazy_creator;
}
Bonus::LazyDestroyer const& SteppedOnBody::getBonusDestroyer() {
    return bonus_destroy_notify;
}


const Bonus::LazyCreator SteppedOnBody::lazy_creator = [] (Snake& snake) {
    return std::unique_ptr<Bonus>(new SteppedOnBody(snake));
};

const Bonus::LazyDestroyer SteppedOnBody::bonus_destroy_notify = [] {
    // Тут делать нечего.
    // Никому не интересно, что часть тела уничтожена,
    // кроме самой змейки.
};
