//
// Created by Lyosha12 on 25.06.2018.
//

#include "SteppedOnBody.hpp"
SteppedOnBody::SteppedOnBody(Snake& snake): Bonus(snake) {
    endGame();
}

bool SteppedOnBody::activate() {
    // Пока что нет функционала - игра завершится.
    return false;
}