//
// Created by Lyosha12 on 25.06.2018.
//

#include "Move.hpp"
#include "../../Snake/Snake.hpp"

Move::Move(Snake& snake): Bonus(snake) {
    // Змейка не может быть нулевой длины.
    snake.popBodyChapter(snake.bodyLength() - 1);
}

bool Move::activate() {
    // Перемещение змейки уже было в конструкторе бонуса.
    // Здесь просто скажем о том, что он уже не нужен -
    // зачем хранить ещё и флаг, применился ли бонус и окончательно ли?
    return false;
}

Bonus::LazyCreator const& Move::getBonusCreator() {
    return lazy_creator;
}

const Bonus::LazyCreator Move::lazy_creator = [] (Snake& snake) {
    return std::unique_ptr<Bonus>(new Move(snake));
};