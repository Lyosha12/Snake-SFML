// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 23.06.2018.
//

#include "AddChapter.hpp"
#include "Snake/Snake.hpp"
#include "CellsPool/Cell/Fillers/BodyAngle.hpp"

AddChapter::AddChapter(Snake& snake): Bonus(snake) {
    // Блок головы уже добавлен в змейку в правильном положении.
    // Пересмотрим текстуру блока перед новой головой (предыдущую голову).
    snake.redefineBodySprite(1);
    
    // И на этом всё. Бонус движения удалял хвост. Но, т.к. это еда,
    // то не удалим хвост, таким образом увеличив количество клеток змейки на 1.
}

bool AddChapter::activate() {
    // Активация уже была в конструкторе, делать больше нечего.
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

