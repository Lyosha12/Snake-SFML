//
// Created by Lyosha12 on 25.06.2018.
//

#include "Move.hpp"
#include "Snake/Snake.hpp"
#include "CellsPool/Cell/Fillers/BodyAngle.hpp"

Move::Move(Snake& snake): Bonus(snake) {
    // Блок головы уже добавлен в змейку в правильном положении.
    // Пересмотрим текстуру блока перед новой головой (предыдущую голову).
    snake.redefineBodySprite(1);
    
    // Теперь удалим часть хвоста.
    snake.popChapter(snake.length() - 1);
    
    // И пересмотрим положение хвоста
    snake.redefineTailSprite();
}

bool Move::activate() {
    // Активация уже была в конструкторе, делать больше нечего.
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
    // Уведомлять никого не нужно.
};