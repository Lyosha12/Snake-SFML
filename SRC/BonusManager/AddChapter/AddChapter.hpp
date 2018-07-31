//
// Created by Lyosha12 on 23.06.2018.
//

#ifndef SNAKE_EAT_HPP
#define SNAKE_EAT_HPP

#include <atomic>
#include "BonusManager/Bonus/Bonus.hpp"
#include "Utility/Timer.hpp"

class AddChapter: public Bonus {
    // Бонус типа "еда" - при взятии увеличивает количество частей змейки.
    
  public:
    using Bonus::Bonus;
    
    bool activate() override;
    
    // Функции для управления едой на поле из менеджера бонусов.
    static bool isExist();
    static bool isTacked();
    
    static LazyCreator const& getBonusCreator();
    static LazyDestroyer const& getBonusDestroyer();
    
  private:
    static const LazyCreator lazy_creator;
    static const LazyDestroyer bonus_destroy_notify;
    
    // Бонус еды имеет не ограниченное время жизни.
    // TODO: По крайней мере, пока этот бонус только один.
    inline static Timer<> existence_timer = { Timer<>::maxInterval() };
    
    //
    inline static std::atomic<bool> is_tacked = true;
};


#endif //SNAKE_EAT_HPP