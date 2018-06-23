//
// Created by Lyosha12 on 23.06.2018.
//

#ifndef SNAKE_BONUS_HPP
#define SNAKE_BONUS_HPP

#include <chrono>
#include "../../Snake/Snake.hpp"
#include "../../CellsPool/CellsPool.hpp"

class Bonus {
  public:
    virtual bool activate(Snake& snake) = 0;
    ~Bonus() = default;
    
    
    
  protected:
  
};


#endif //SNAKE_BONUS_HPP
