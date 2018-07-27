//
// Created by Lyosha12 on 23.06.2018.
//

#ifndef SNAKE_BONUSMANAGER_HPP
#define SNAKE_BONUSMANAGER_HPP

#include <atomic>
#include "../CellsPool/Cell/Cell.hpp"


class CellsPool;
class LiveStorage;
class BonusManager {
    // В отдельном потоке следит за появлением и удалением бонусов на поле.
    
  public:
    BonusManager(CellsPool& cells_pool);
    void operator() (LiveStorage& live_storage);
    
  private:
    void trySetEat();
    
  private:
    CellsPool& cells_pool;
    Cell::CellCPtr eat = nullptr; // Отвечает за хранение и возврат клетки с бонусом Eat.
};


#endif //SNAKE_BONUSMANAGER_HPP
