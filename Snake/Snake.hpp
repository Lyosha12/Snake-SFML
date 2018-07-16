//
// Created by Lyosha12 on 22.06.2018.
//

#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP

#include <queue>
#include <vector>
#include <chrono>
using namespace std::chrono_literals;

#include "../Utilites/Coord/Coord.hpp"
#include "../Utilites/TimeCounter/TimeCounter.hpp"
#include "../Utilites/ListRunner.hpp"
#include "../CellsPool/Cell/Cell.hpp"
#include "../BonusManager/Bonus/Bonus.hpp"
#include "../CellsPool/CellsPool.hpp"

class Snake {
    using CellCPtr = Cell::CellCPtr;
  
  public:
    enum class Direction { Up, Down, Left, Right };
  
  public:
    Snake(CellsPool& cells_pool);
    
    void move();
    void changeDirection(Direction direction);
    
  public:
    // Считая с головы-нуля, удаляет запрошенный элемент змейки.
    void popChapter(size_t chapter_index);
    
    // Вставить переданный заполнитель (обычно тело, если вызывает бонус движения)
    // перед указанным элементом змейки, считая с нуля.
    // Так, можно сделать телом змейки и заполнитель-бонус.
    // Получаются интересные варианты геймплея.
    template <class FillerType>
    void pushChapter(size_t chapter_index);
    
    template <class InputFiller>
    void replaceChapter(size_t chapter_index);
    
    size_t bodyLength() const;
    auto getMoveInterval() const;
    template <class IntervalType>
    void setMoveInterval(IntervalType move_interval);
    
  private:
    void addHead();
    void addBody();
    void findHeadDirection();
    void tryChangeDirection();
    void applyEffects();
  
  private:
    std::list<CellCPtr> body;
    Coord direction = {0, 0};
    TimeCounter<> move_interval = 650ms;
    std::queue<Coord> moves;
    
    CellsPool& cells_pool;
    std::list<std::unique_ptr<Bonus>> active_effects;
};

#include "Snake.tpl.cpp"


#endif //SNAKE_SNAKE_HPP
