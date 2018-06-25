//
// Created by Lyosha12 on 22.06.2018.
//

#include <iostream>
#include "Snake.hpp"
#include "SnakeFillers/Body/Body.hpp"
#include "SnakeFillers/Head/Head.hpp"
#include "../CellsPool/CellsPool.hpp"

Snake::Snake(CellsPool& cells_pool)
: cells_pool(cells_pool)
{
    std::lock_guard<CellsPool> lock(cells_pool);
    Snake::addHead();
    Snake::addBody();
    Snake::findHeadDirection();
}

void Snake::move() {
    if(!move_interval.isIntervalPassed()) {
        applyEffects(); // Если не время хода, выполним другую работу.
        return;
    }
    
    // Пока ещё не начали двигаться, посмотрим, нужно ли изменить направление.
    tryChangeDirection();
    
    std::lock_guard<CellsPool> lock(cells_pool);
    
    // Получим новую голову по направлению движения относительно текущей головы.
    CellsPool::RequestedCell new_head = cells_pool.getCell<Head>(body.front(), direction);
    
    // Указатель тогда nullptr, когда клеткой уже кто-то владел -
    // нельзя просто взять и удалить чужой заполнитель.
    // Получив уже занятую клетку, переместиться в неё нельзя.
    if(new_head.prev_filler != nullptr) {
    
        // Освободим клетку старой головы.
        // Было: { HB};
        popBodyChapter(0);
        // Теперь: { B};
    
        // * Добавим часть тела в список между новой головой и удалённой прошлой.
        // * Ингорируем бонус - клеткой только что владела старая голова.
        body.push_front(cells_pool.getCell<Body>(new_head.cell, -direction).cell);
        // Теперь: { BB};
        
        // Добавим вслед за частью тела новую голову.
        body.push_front(new_head.cell);
        // Теперь: {HBB}.
    }
    
    // Добавим бонус с этой клетки в список активных бонусов змейки.
    this->active_effects.push_back(
        // Учитывая, что предыдущий заполнитель может остаться на месте,
        // указатель может быть нулевым.
        // Тогда очевидно, что предыдущий заполнитель остался
        // в запрошенной клетке, которая не изменила состояния и
        // в которую змейка не перепестилась.
        (
            new_head.prev_filler
            ? new_head.prev_filler
            : new_head.cell->filler
        )->getBonus(*this)
        
        // При попытке хода в текущем интервале времени будет выполнен
        // проход по собранным бонусам. Тогда же змейка будет либо
        // укорочена {HB } - бонус свободной клетки,
        // либо останется прежней {HBB} - бонус еды.
        // Другой бонус может изменить змейку как-то ещё через её интерфейс.
    );
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
            // т.к. ещё не запущен менеджер бонусов,
            // да и заблокирован он. Поэтому игнорируем бонус.
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
    // Извлечём из очереди идемпотентные или
    // прямо противоположные текущему направлению ходы.
    while(!moves.empty() && (moves.front() + direction == 0 || moves.front() == direction))
        moves.pop();
    
    // Применим одно пожелание игрока на текущем интервале.
    if(!moves.empty()) {
        direction = moves.front();
        moves.pop();
    }
}
void Snake::applyEffects() {
    for(auto i = active_effects.begin(); i != active_effects.end(); ) {
        if(!(*i)->activate()) {
            i = active_effects.erase(i);
        } else {
            ++i;
        }
    }
}