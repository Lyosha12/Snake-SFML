//
// Created by Lyosha12 on 23.06.2018.
//

#include "AddChapter.hpp"
#include "Snake/Snake.hpp"
#include "CellsPool/Cell/Fillers/Body.hpp"

bool AddChapter::activate() {
    // Поменяем старую голову на часть тела, как при перемещении.
    snake.replaceChapter<Body>(1);
    
    // И на этом всё. Бонус движения удалял хвост. Но, т.к. это еда,
    // то не удалим хвост, таким образом увеличив количество клеток змейки на 1.
    return false;
}

Bonus::LazyCreator const& AddChapter::getBonusCreator() {
    AddChapter::existence_timer.reset();
    AddChapter::is_tacked = false;
    
    return AddChapter::lazy_creator;
}
Bonus::LazyDestroyer const& AddChapter::getBonusDestroyer() {
    return bonus_destroy_notify;
}

bool AddChapter::isExist() {
    return !AddChapter::existence_timer.isIntervalExpire() && !AddChapter::isTacked();
}
bool AddChapter::isTacked() {
    return AddChapter::is_tacked;
}


const Bonus::LazyCreator AddChapter::lazy_creator = [] (Snake& snake) {
    AddChapter::is_tacked = true;
    return std::unique_ptr<Bonus>(new AddChapter(snake));
};

const Bonus::LazyDestroyer AddChapter::bonus_destroy_notify = [] {
    // Клетка не взята.
    // Обнулим таймер её существования (и он начнётся сразу же заново)...
    // TODO: Может, использовать здесь секундомер?
    AddChapter::existence_timer.reset();
};

