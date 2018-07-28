//
// Created by Lyosha12 on 25.06.2018.
//

#include "Move.hpp"
#include "Snake/Snake.hpp"
#include "CellsPool/Cell/Fillers/Body.hpp"

Move::Move(Snake& snake): Bonus(snake) {
    // Заменим предыдущую голову змейки на часть тела.
    snake.replaceChapter<Body>(1);
    
    // Змейка не может быть нулевой длины. Удалим хвост.
    snake.popChapter(snake.bodyLength() - 1);
}

bool Move::activate() {
    // Перемещение змейки уже было в конструкторе бонуса.
    // Здесь просто скажем о том, что он уже не нужен.
    return false;
}

Bonus::LazyCreator const& Move::getBonusCreator() {
    return lazy_creator;
}
Bonus::LazyDestroyer const& Move::getBonusDestroyer() {
    return bonus_destroy_notify;
}




const Bonus::LazyCreator Move::lazy_creator = [] (Snake& snake) {
    return std::unique_ptr<Bonus>(new Move(snake));
};

const Bonus::LazyDestroyer Move::bonus_destroy_notify = [] {
    // Разрушение заполнителя клетки типа "свободная клетка".
    // Вроде уведомлять никого не нужно.
};