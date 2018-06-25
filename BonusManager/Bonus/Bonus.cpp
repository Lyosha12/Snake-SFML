//
// Created by Lyosha12 on 23.06.2018.
//

#include <cstdlib>
#include "Bonus.hpp"

void endGame() {
    std::exit(0xE9D);
}

Bonus::Bonus(Snake& snake): snake(snake) { }