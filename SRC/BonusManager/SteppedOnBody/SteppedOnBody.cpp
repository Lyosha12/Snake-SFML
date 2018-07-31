//
// Created by Lyosha12 on 25.06.2018.
//

#include "Snake/GameEnd.hpp"
#include "SteppedOnBody.hpp"

bool SteppedOnBody::activate() {
    throw GameEnd("Game is end");
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
};
