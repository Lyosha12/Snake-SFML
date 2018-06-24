//
// Created by Lyosha12 on 23.06.2018.
//

#ifndef SNAKE_BONUSMANAGER_HPP
#define SNAKE_BONUSMANAGER_HPP

#include <atomic>
#include "../CellsPool/CellsPool.hpp"
#include "../TimeCounter/TimeCounter.hpp"

class BonusManager {
    // В отдельном потоке следит за появлением и удалением бонусов на поле.
    
  public:
    BonusManager(CellsPool& cells_pool): cells_pool(cells_pool) { }
    
    void operator() (std::atomic<bool>& is_program_work) {
        while(is_program_work) {
            trySetEat();
        }
    }
    
    void trySetEat() {
    
    }
  
  private:
    CellsPool& cells_pool;
};


#endif //SNAKE_BONUSMANAGER_HPP
