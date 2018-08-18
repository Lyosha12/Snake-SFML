//
// Created by Lyosha12 on 23.06.2018.
//

#include "CellsPool/CellsPool.hpp"
#include "Utility/ThreadGuard/LiveStorage/LiveStorage.hpp"
#include "Utility/FatalError/FatalError.hpp"
#include "CellsPool/Cell/Fillers/Eat.hpp"

#include "BonusManager.hpp"

BonusManager::BonusManager(CellsPool& cells_pool)
: cells_pool(cells_pool)
    // Не знаю почему, но передача *this как функтора не работает
    // в конструкторе, хотя работает вне конструктора.
, thread([this] (LiveStorage& live_storage) { run(live_storage); })
{ }

void BonusManager::run(LiveStorage& live_storage) {
    try {
        while(live_storage) {
            trySetEat();
        }
        
    } catch(std::exception const& e) {
        FatalError(e.what()).print();
    }
}

void BonusManager::trySetEat() {
    // Установим новую еду, если её нет на поле.
    bool x = !AddChapter::isExist();
    if(x) {
        // Это не срочно. Можно подождать пару циклов
        // и установить в период бездействия змейки.
        std::unique_lock<CellsPool> lock(cells_pool, std::defer_lock);
        while(!lock.try_lock())
            ;
        
        // Клетка принадлежит менеджеру бонусов, если бонус исчез
        // и клеткой никто не завладел.
        if(!AddChapter::isTacked()) {
            cells_pool.releaseCell(eat);
        }
        
        eat = cells_pool.getRandCell(Filler::makeFillerCreator<Eat>(0)).cell;
    }
}
    
