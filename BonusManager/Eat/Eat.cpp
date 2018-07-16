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
    is_exist = true;
    return lazy_creator;
}

Bonus::LazyDestroyer const& Eat::getBonusDestroyer() {
    return bonus_destroy_notify;
}

bool Eat::isExists() {
    return is_exist;
}



const Bonus::LazyCreator Eat::lazy_creator = [] (Snake& snake) {
    return std::unique_ptr<Bonus>(new Eat(snake));
};

const Bonus::LazyDestroyer Eat::bonus_destroy_notify = [] {
    is_exist = false;
};

