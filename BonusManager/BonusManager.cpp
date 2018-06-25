//
// Created by Lyosha12 on 23.06.2018.
//

#include "BonusManager.hpp"

BonusManager::BonusManager(CellsPool& cells_pool): cells_pool(cells_pool) { }

void BonusManager::operator() (std::atomic<bool>& is_program_work) {
    while(is_program_work) {
    
    }
}

void BonusManager::trySetEat() {

}