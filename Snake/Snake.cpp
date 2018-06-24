//
// Created by Lyosha12 on 22.06.2018.
//

#include "Snake.hpp"

Snake::Snake(CellsPool& cells_pool)
: cells_pool(cells_pool)
{
    std::lock_guard<CellsPool> lock(cells_pool);
    Snake::addHead();
    Snake::addBody();
    Snake::findHeadDirection();
}

void Snake::move() {
    if(!move_interval.isIntervalPassed())
        return;
    
    tryChangeDirection();
    
    std::lock_guard<CellsPool> lock(cells_pool);
    // Получим новую голову по направлению движения относительно текущей головы.
    CellsPool::RequestedCell new_head = cells_pool.getCell<Head>(body.front(), direction);
    
    // Получив уже занятую клетку, переместиться в неё нельзя. Значит,
    // остаётся только позволить заполнителю этой клетки сделать своё дело.
    if(new_head.prev_filler->isFree()) {
    
        // Освободим клетку старой головы.
        popBodyChapter(0);
    
        // Добавим часть тела в список между новой головой и удалённой прошлой.
        // Т.к. бонус не мог появиться между удалением текущей головы и
        // добавлением части тела вместо неё,
        // будем игнорировать прошлый заполнитель клетки.
        body.push_front(cells_pool.getCell<Body>(new_head.cell, -direction).cell);
        // Добавим вслед за частью тела новую голову.
        body.push_front(new_head.cell);
    }
    
    // Дадим возможность заполнителю клетки изменить змейку.
    new_head.prev_filler->modify(*this);
}
void Snake::changeDirection(Direction direction) {
    // Внешнее управление змейкой посредством пользовательского ввода.
    switch(direction) {
        case Direction::Up   : moves.push({ 0, -1}); break;
        case Direction::Down : moves.push({ 0,  1}); break;
        case Direction::Left : moves.push({-1,  0}); break;
        case Direction::Right: moves.push({ 1,  0}); break;
    }
}


void Snake::popBodyChapter(size_t chapter_index) {
    auto chapter = getListElement(body, chapter_index);
    cells_pool.releaseCell(*chapter);
    body.erase(chapter);
}


size_t Snake::bodyLength() const {
    return body.size();
}
auto Snake::getMoveInterval() const {
    return move_interval.getInterval();
}

void Snake::addHead() {
    // Разместим голову в случайном месте поля.
    CellsPool::RequestedCell head = cells_pool.getRandCell<Head>();
    body.push_back(head.cell);
}
void Snake::addBody() {
    // Создадим параметры змейки.
    size_t max_start_parts = 4;
    size_t guaranteed_parts = 2;
    size_t additional_parts = rand()%(max_start_parts - guaranteed_parts);
    size_t start_parts = additional_parts + guaranteed_parts;
    
    // Сгенерируем остальное тело.
    try {
        while(start_parts--) {
            // Полученная клетка не может быть бонусной,
            // т.к. ещё не запущен менеджер бонусов.
            body.push_back(cells_pool.getNearCell<Body>(body.back()).cell);
        }
    } catch(NotFoundFreeCell const& e) {
        // Заканчиваем построение змеи - нет клеток для продолжения.
    }
}
void Snake::findHeadDirection() {
    // Узнаем направление змейки. От координат головы
    // отнимем координаты блока перед головой.
    Cell const* head = *body.begin();
    Cell const* prev_head = *++body.begin();
    direction = head->coord - prev_head->coord;
}
void Snake::tryChangeDirection() {
    while(!moves.empty() && (moves.front() + direction == 0 || moves.front() == direction))
        moves.pop();
    
    if(!moves.empty()) {
        direction = moves.front();
        moves.pop();
    }
}