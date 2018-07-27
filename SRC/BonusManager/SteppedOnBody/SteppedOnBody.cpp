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
    // Ну что можно сказать, когда часть змейки уничтожилась...
    // Разве что эффект воспроизвести... Но это можно сделать и в
    // деструкторе клетки. Пустышка ещё одна, в общем.
};
