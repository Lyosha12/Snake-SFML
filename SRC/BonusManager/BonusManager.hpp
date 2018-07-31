//
// Created by Lyosha12 on 23.06.2018.
//

#ifndef SNAKE_BONUSMANAGER_HPP
#define SNAKE_BONUSMANAGER_HPP

#include <atomic>
#include "CellsPool/Cell/Cell.hpp"
#include "Utility/ThreadGuard/ThreadGuard.hpp"


class CellsPool;
class LiveStorage;
class BonusManager {
    // В отдельном потоке следит за появлением и удалением бонусов на поле.
    // TODO: Пока что выполняет функции только AddChapter-контроллера.
    
  public:
    BonusManager(CellsPool& cells_pool);
    
  private:
    void run(LiveStorage& live_storage);
    void trySetEat();
    
  private:
    CellsPool& cells_pool;
    Cell::CellCPtr eat = nullptr; // Отвечает за хранение и возврат клетки с бонусом AddChapter.
    ThreadGuard thread;
};


#endif //SNAKE_BONUSMANAGER_HPP
