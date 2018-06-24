//
// Created by Lyosha12 on 22.06.2018.
//

#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP

#include <queue>
#include <vector>
#include <chrono>
using namespace std::chrono_literals;

#include "../CellsPool/Cell/Cell.hpp"
#include "../CellsPool/CellsPool.hpp"
#include "../TimeCounter/TimeCounter.hpp"
#include "../Utilites/ListRunner.hpp"
#include "SnakeFillers/Body/Body.hpp"
#include "SnakeFillers/Head/Head.hpp"

class Snake {
    using CellCPtr = Cell::CellCPtr;
    
  private:
  
  public:
    enum class Direction { Up, Down, Left, Right };
  
  public:
    Snake(CellsPool& cells_pool);
    
    void move();
    void changeDirection(Direction direction);
    
  public:
    void popBodyChapter(size_t chapter_index);
    size_t bodyLength() const;
    auto getMoveInterval() const;
    template <class IntervalType>
    void setMoveInterval(IntervalType move_interval) {
        this->move_interval.setInterval(move_interval);
    }
    
  private:
    void addHead();
    void addBody();
    void findHeadDirection();
    void tryChangeDirection();
  
  private:
    std::list<CellCPtr> body;
    Coord direction = {0, 0};
    TimeCounter<> move_interval = 150ms;
    std::queue<Coord> moves;
    
    CellsPool& cells_pool;
};


#endif //SNAKE_SNAKE_HPP
