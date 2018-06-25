//
// Created by Lyosha12 on 23.06.2018.
//

#ifndef SNAKE_BONUS_HPP
#define SNAKE_BONUS_HPP

#include "../../Snake/Snake.hpp"
#include "../../CellsPool/CellsPool.hpp"


// FIXME: Временно голова и тело выполняют одну и ту же операцию
// При попытке взять их игра завершиться.
// Для мультиплеера нужно расширить идею.
void endGame();

class Bonus {
  public:
    Bonus(Snake& snake);
    Bonus(Bonus const&) = delete;
    Bonus& operator= (Bonus const&) = delete;
    
    virtual bool activate() = 0;
    
    ~Bonus() = default;
    
  protected:
    Snake& snake;
};


#endif //SNAKE_BONUS_HPP
