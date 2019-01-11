//
// Created by Lyosha12 on 22.06.2018.
//

#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP

#include <queue>
#include <vector>

#include "Utility/Coord/Coord.hpp"
#include "Utility/ListRunner.hpp"
#include "CellsPool/Cell/Cell.hpp"
#include "BonusManager/Bonus/Bonus.hpp"
#include "CellsPool/CellsPool.hpp"
#include "Utility/Timer.hpp"

class Snake {
    using CellCPtr = Cell::CellCPtr;
  
  public:
    enum class Direction { Up, Down, Left, Right };
  
  public:
    Snake(CellsPool& cells_pool);
    
    void move();
    void changeDirection(Direction direction);
    
    Coord redefineHeadSprite() const;
    Coord redefineTailSprite() const;
    Coord redefineBodySprite(size_t chapter_index) const;
    
  public:
    // Считая с головы-нуля, удаляет запрошенный элемент змейки.
    void popChapter(size_t chapter_index);
    
    // Заменить заполнитель в клетке змейки на что-то другое.
    void replaceChapter(size_t chapter_index, Filler::FillerCreator filler_creator);
    
    size_t length() const;
    auto getMoveInterval() const;
    void setMoveInterval(std::chrono::milliseconds move_interval);
    
  private:
    void tryChangeDirection();
    void applyEffects();
    void startInitialize();
  
  private:
    std::list<CellCPtr> body;
    Coord direction = {0, 0};
    Timer<> move_interval = 120ms;
    std::queue<Coord> moves;
    
    CellsPool& cells_pool;
    std::list<std::unique_ptr<Bonus>> active_effects;
};


#endif //SNAKE_SNAKE_HPP
