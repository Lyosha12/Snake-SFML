// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 22.06.2018.
//

#include "Snake.hpp"
#include "Utility/Trivials/Trivials.hpp"
#include "Utility/Coord/Coord.hpp"
#include "CellsPool/CellsPool.hpp"
#include "CellsPool/Cell/Fillers/Head.hpp"
#include "CellsPool/Cell/Fillers/Tail.hpp"
#include "CellsPool/Cell/Fillers/BodyAngle.hpp"
#include "CellsPool/Cell/Fillers/BodyStraight.hpp"
#include "CellsPool/Cell/Fillers/NullFiller.hpp"

Snake::Snake(CellsPool& cells_pool)
: cells_pool(cells_pool)
{
    std::lock_guard<CellsPool> lock(cells_pool);
 
    emptyInitialize();
    
    // Переопределим голову.
    direction = redefineHeadSprite();
    
    // Переопределим хвост.
    redefineTailSprite();
    
    // Пройдёмся по телу и определим его спрайты.
    // Гарантируется, что тело состоит по крайней мере из двух частей.
    for(size_t i = 1; i != body.size() - 1; ++i) {
        redefineBodySprite(i);
    }
}

// TODO: Переименовать в update, разделить ответственность.
void Snake::move() {
    if(!move_interval.isIntervalExpire()) {
        applyEffects(); // Если не время хода, выполним другую работу.
        return;
    }
    
    move_interval.reset();
    
    // Пока ещё не начали двигаться, попробуем изменить направление.
    tryChangeDirection();
    
    std::lock_guard<CellsPool> lock(cells_pool);
    
    // Получим новую голову по направлению движения относительно текущей головы.
    CellsPool::RequestedCell new_head = cells_pool.getCell(
        body.front(), direction,
        Filler::makeFillerCreator<Head>(angle(direction, Head::orientation))
    );
    
    // Добавим новую голову к телу, если эта клетка свободна.
    // Предыдущий заполнитель клетки должен быть перемещён в член prev_filler.
    if(new_head.prev_filler != nullptr) {
        body.push_front(new_head.cell);
    }
    
    // Добавим бонус с этой клетки в список активных бонусов змейки.
    this->active_effects.push_back(
        // Возьмём бонус с полученной клетки (new_head.prev_filler).
        // Если клетку не получили, то заполнитель там старый (new_head.cell->filler)
        (
            new_head.prev_filler
            ? new_head.prev_filler
            : new_head.cell->filler
        )->getBonus(*this)
    );
    
}
void Snake::changeDirection(Direction incoming_direction) {
    // Внешнее управление змейкой посредством пользовательского ввода.
    switch(incoming_direction) {
        case Direction::Up   : moves.push({ 0, -1}); break;
        case Direction::Down : moves.push({ 0,  1}); break;
        case Direction::Left : moves.push({-1,  0}); break;
        case Direction::Right: moves.push({ 1,  0}); break;
    }
}

static void normalize_invert (Coord& vector) {
    static double constexpr simple_square_diagonal = M_SQRT2 + 0.5;
    if((simple_square_diagonal < vector.length())) {
        vector *= -1;
        vector.x = sign(vector.x);
        vector.y = sign(vector.y);
    }
}
Coord Snake::redefineHeadSprite() const {
    // Узнаем направление головы змейки.
    // От координат головы отнимем координаты блока перед головой.
    CellCPtr head = body.front();
    CellCPtr prev_head = *getListElement(body, 1);
    
    Coord head_direction = head->coord - prev_head->coord;
    
    // Смотри redefineBodySprite.
    normalize_invert(head_direction);
    
    // Вычислим поворот спрайта головы относительно
    // положения головы на спрайте (1, 0).
    // После этого заменим пустышку на правильный спрайт головы.
    cells_pool.replaceFiller(
        body.front(),
        Filler::makeFillerCreator<Head>(angle(head_direction, Head::orientation))
    );
    
    return head_direction;
}
Coord Snake::redefineTailSprite() const {
    // Узнаем направление хвоста змейки.
    // От координат хвоста отнимем координаты блока перед хвостом.
    CellCPtr tail = body.back();
    CellCPtr prev_tail = *getListElement(body, body.size() - 2);
    Coord tail_direction = tail->coord - prev_tail->coord;
    
    // Смотри redefineBodySprite.
    normalize_invert(tail_direction);
    
    // Аналогично вычислим отклонение направления хвоста от того,
    // как он расположен на спрайте.
    // Создадим новый спрайт и заменим пустышку.
    cells_pool.replaceFiller(
        body.back(),
        Filler::makeFillerCreator<Tail>(
            angle(tail_direction, Tail::orientation)
        )
    );
    
    return tail_direction;
}
Coord Snake::redefineBodySprite(size_t chapter_index) const {
    // Определим вектор направления части тела как диагональ,
    // которую образовывают векторы направления, выходящие из
    // текущей части тела.
    using Iterator = decltype(body.begin());
    Iterator i = getListElement(body, chapter_index);
    Coord a = (*--Iterator(i))->coord - (*i)->coord;
    Coord b = (*++Iterator(i))->coord - (*i)->coord;
    
    /* При переходе через границу поля возникает ситуация,
       когда два блока отстают друг от друга больше,
       чем на единичный вектор перемещения.
       
       Переходить через границу можно только на противоположную.
       Поэтому, если длина одного из векторов 'a' или 'b'
       будет больше, чем длина диагонали единичного квадрата, то,
       чтобы поворот текстуры был правильным,
       нужно обратить направление такого вектора.
       
       Кроме того, одна из компонент вектора диагонали
       может быть не равна другой.
       Тогда получится, что это и не диагональ вовсе.
       Следовательно, нужно также привести всё к единичным компонентам.
     */
    normalize_invert(a);
    normalize_invert(b);
    
    
    // Есть две части тела - прямая и изгиб.
    if(!isCollinear(a, b)) { // Это изгиб.
        Coord diagonal = a + b;
        cells_pool.replaceFiller(
            *i,
            Filler::makeFillerCreator<BodyAngle>(
                angle(diagonal, BodyAngle::orientation)
            )
        );
        
        return diagonal;
    } else {
        // Иначе имеем два коллинеарных вектора.
        // Выберем из них один и вычислим угол поворота
        // прямой части тела.
        cells_pool.replaceFiller(
            *i,
            Filler::makeFillerCreator<BodyStraight>(
                angle(a, BodyStraight::orientation)
            )
        );
        
        return a;
    }
}

void Snake::popChapter(size_t chapter_index) {
    auto chapter = getListElement(body, chapter_index);
    cells_pool.releaseCell(*chapter);
    body.erase(chapter);
}
void Snake::replaceChapter(size_t chapter_index, Filler::FillerCreator filler_creator) {
    // Замена заполнителя - работа бассейна клеток. Переадресуем.
    cells_pool.replaceFiller(*getListElement(body, chapter_index), filler_creator);
}

size_t Snake::length() const {
    return body.size();
}
auto Snake::getMoveInterval() const {
    return move_interval.getInterval();
}
void Snake::setMoveInterval(std::chrono::milliseconds move_interval) {
    this->move_interval.setInterval<std::chrono::milliseconds>(move_interval);
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
void Snake::emptyInitialize() {
    // Для начала создадим тело змейки из пустышек.
    size_t guaranteed_parts = 2;
    size_t max_parts = 4;
    size_t additional_parts = random()%(max_parts - guaranteed_parts);
    size_t missing_parts = guaranteed_parts + additional_parts;
    
    // Игнорируем любые возможные бонусы.
    // Добавим голову и остальные части.
    body.push_back(
        cells_pool.getRandCell(Filler::makeFillerCreator<NullFiller>(0)).cell
    );
    
    while(missing_parts--) {
        body.push_back(
            cells_pool.getNearCell(
                body.back(), Filler::makeFillerCreator<NullFiller>(0)
            ).cell
        );
    }
}
