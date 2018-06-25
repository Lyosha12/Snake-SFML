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