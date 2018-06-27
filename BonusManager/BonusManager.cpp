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
    // Бонус существует на поле и менеджер бонусов им владеет.
    if(eat != nullptr && Eat::isExists()) { // Normal program state.
        return;
    }
    
    // Бонуса на поле нет и мы им не владеем.
    if(eat == nullptr && !Eat::isExists()) {
        // Тогда создадим бонус и будем им владеть.
        std::lock_guard<CellsPool> lock(cells_pool);
        eat = cells_pool.getRandCell<EatFiller>().cell;
        return;
    }
    // Если бонусом менеджер владеет и бонус не существует на поле,
    // то нужно освободить клетку.
    // Произойдёт, когда время существования бонуса, если оно есть, пройдёт.
    // TODO: Нельзя определить принадлежит ли нам клетка или нет только по наличию бонуса на поле.
     if(eat != nullptr && !Eat::isExists()) {
        std::lock_guard<CellsPool> lock(cells_pool);
        cells_pool.releaseCell(eat);
        
        return;
    }
    
    if(eat == nullptr && Eat::isExists()) { // WTF-Branch
        throw std::logic_error(
            "Eat are exists on field, but pointer eat == nullptr.\n"
            "Cannot to release eat bonus"
        );
    }
}
    
