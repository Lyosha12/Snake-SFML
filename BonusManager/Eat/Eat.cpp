//
// Created by Lyosha12 on 23.06.2018.
//

#include "Eat.hpp"
#include "../../Snake/Snake.hpp"
#include "../../CellsPool/Cell/Fillers/Body.hpp"

Eat::Eat(Snake& snake): Bonus(snake) {
    // Поменяем старую голову на часть тела, как при перемещении.
    snake.replaceChapter<Body>(1);
    
    // И на этом всё. Бонус движения удалял хвост. Но, т.к. это еда,
    // то не удалим хвост, таким образом увеличив количество клеток змейки на 1.
}

bool Eat::activate() {
    // Активация не нужна.
    // Бонус уже "подействовал" конструктором, не удаляя хвост змейки.
    // Поэтому просто скажем, что в списке активных бонусов он лишний.
    return false;
}

Bonus::LazyCreator const& Eat::getBonusCreator() {
    Eat::existence_timer.reset();
    Eat::is_tacked = false;
    
    return Eat::lazy_creator;
}
Bonus::LazyDestroyer const& Eat::getBonusDestroyer() {
    return bonus_destroy_notify;
}

bool Eat::isExist() {
    return !Eat::existence_timer.isIntervalExpire() && !Eat::is_tacked;
}
bool Eat::isTacked() {
    return Eat::is_tacked;
}


const Bonus::LazyCreator Eat::lazy_creator = [] (Snake& snake) {
    Eat::is_tacked = true;
    return std::unique_ptr<Bonus>(new Eat(snake));
};

const Bonus::LazyDestroyer Eat::bonus_destroy_notify = [] {
    Eat::existence_timer.reset();
};

