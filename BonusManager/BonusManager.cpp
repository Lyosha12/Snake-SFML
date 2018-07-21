//
// Created by Lyosha12 on 23.06.2018.
//

#include "BonusManager.hpp"
#include "../CellsPool/CellsPool.hpp"
#include "../Utilites/ThreadGuard/LiveStorage/LiveStorage.hpp"
#include "../Utilites/ErrorPrinter/ErrorPrinter.hpp"
#include "../CellsPool/Cell/Fillers/EatFiller.hpp"

BonusManager::BonusManager(CellsPool& cells_pool): cells_pool(cells_pool) { }

void BonusManager::operator() (LiveStorage& live_storage) {
    try {
        while(live_storage) {
            trySetEat();
        }
    } catch(std::exception const& e) {
        ErrorPrinter(e.what()).print();
    }
}

void BonusManager::trySetEat() {
    // Установим новую еду, если её нет на поле.
    bool x = !Eat::isExist();
    if(x) {
        // Это не срочно. Можно подождать пару циклов
        // и установить в период бездействия змейки.
        std::unique_lock<CellsPool> lock(cells_pool, std::defer_lock);
        while(!lock.try_lock())
            ;
        
        // Клетка принадлежит менеджеру бонусов, если бонус исчез
        // и клеткой никто не завладел.
        if(!Eat::isTacked()) {
            cells_pool.releaseCell(eat);
        }
        
        eat = cells_pool.getRandCell<EatFiller>().cell;
    }
}
    
