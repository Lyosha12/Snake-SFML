//
// Created by Lyosha12 on 22.06.2018.
//

#include "Snake.hpp"

Snake::SnakeHead::SnakeHead(DefaultRectangle const& default_rectangle, Coord const& coord)
    : Filler(default_rectangle, coord, texture, false)
{  }
Snake::SnakeBody::SnakeBody(DefaultRectangle const& default_rectangle, Coord const& coord)
    : Filler(default_rectangle, coord, texture, false)
{  }



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
    RequestedCell new_head = cells_pool.getNearCell<SnakeHead>(body.front(), direction);
    
    // Освободим клетку старой головы.
    cells_pool.releaseCell(body.front());
    // Удалим старую голову из списка.
    body.pop_front();
    
    // Добавим часть тела в список между новой головой и удалённой прошлой.
    // Т.к. бонус не мог появиться между удалением текущей головы и
    // добавлением части тела вместо неё,
    // будем игнорировать прошлый заполнитель клетки.
    body.push_front(cells_pool.getNearCell<SnakeBody>(new_head.cell, -direction).cell);
    // Добавим вслед за частью тела новую голову.
    body.push_front(new_head.cell);
    
    // Освободим клетку хвоста.
    cells_pool.releaseCell(body.back());
    body.pop_back();
    
    // Дадим возможность потенциальному бонусу на клетке, где теперь
    // нахдится голова змейки, изменить змейку.
    new_head.modify(*this);
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

size_t Snake::bodyLength() const {
    return body.size();
}
auto Snake::getMoveInterval() const {
    return move_interval.getInterval();
}

void Snake::addHead() {
    // Разместим голову в случайном месте поля.
    // Потом, если попали на какую-то бонусную клетку,
    // применим бонус с неё.
    RequestedCell head = cells_pool.getRandCell<SnakeHead>();
    body.push_back(head.cell);
    head.modify(*this);
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
            // Полученная клетка может быть бонусной.
            RequestedCell body_part = cells_pool.getNearCell<SnakeBody>(body.back());
            
            body.push_back(body_part.cell);
            // Поэтому после присоединения её к телу дадим возможность бонусу изменить змейку.
            body_part.modify(*this);
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