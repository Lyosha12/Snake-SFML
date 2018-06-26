//
// Created by Lyosha12 on 23.06.2018.
//

#include "BonusManager.hpp"
#include "../CellsPool/CellsPool.hpp"
#include "../Utilites/ThreadGuard/LiveStorage/LiveStorage.hpp"
#include "Eat/Eat.hpp"
#include "../Utilites/ErrorPrinter/ErrorPrinter.hpp"
#include "EatFiller/EatFiller.hpp"

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
    if(Eat::isExists() && eat != nullptr) { // Normal program state.
        return;
    }
    
    if(!Eat::isExists() && eat == nullptr) {
        std::lock_guard<CellsPool> lock(cells_pool);
        eat = cells_pool.getRandCell<EatFiller>().cell;
        
    } else if(!Eat::isExists() && eat != nullptr) {
        std::lock_guard<CellsPool> lock(cells_pool);
        cells_pool.releaseCell(eat);
        
    } else // if(Eat::isExists() && eat == nullptr) { // WTF-Branch
        throw std::logic_error(
            "Eat are exists on field, but pointer eat == nullptr.\n"
            "Cannot to release eat bonus"
        );
}
    
