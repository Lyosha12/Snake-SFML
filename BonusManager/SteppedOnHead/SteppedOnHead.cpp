//
// Created by Lyosha12 on 25.06.2018.
//

#include "SteppedOnHead.hpp"
SteppedOnHead::SteppedOnHead(Snake& snake): Bonus(snake) {
    endGame();
}

bool SteppedOnHead::activate() {
    // Пока что нет функционала - игра завершится.
    return false;
}

Bonus::LazyCreator const& SteppedOnHead::getBonusCreator() {
    return lazy_creator;
}

const Bonus::LazyCreator SteppedOnHead::lazy_creator = [] (Snake& snake) {
    return std::unique_ptr<Bonus>(new SteppedOnHead(snake));
};