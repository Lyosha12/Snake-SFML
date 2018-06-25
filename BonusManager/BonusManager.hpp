//
// Created by Lyosha12 on 23.06.2018.
//

#ifndef SNAKE_BONUSMANAGER_HPP
#define SNAKE_BONUSMANAGER_HPP

#include <atomic>

class CellsPool;
class BonusManager {
    // В отдельном потоке следит за появлением и удалением бонусов на поле.
    
  public:
    BonusManager(CellsPool& cells_pool);
    
    void operator() (std::atomic<bool>& is_program_work);
    
    void trySetEat();
  
  private:
    CellsPool& cells_pool;
};


#endif //SNAKE_BONUSMANAGER_HPP
