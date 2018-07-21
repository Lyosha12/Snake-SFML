//
// Created by Lyosha12 on 23.06.2018.
//

#ifndef SNAKE_EAT_HPP
#define SNAKE_EAT_HPP

#include <atomic>
#include "../Bonus/Bonus.hpp"
#include "../../Utilites/Timer.hpp"

class Eat: public Bonus {
  public:
    Eat(Snake& snake);
    
    bool activate() override;
    static bool isExist();
    static bool isTacked();
    
    static LazyCreator const& getBonusCreator();
    static LazyDestroyer const& getBonusDestroyer();
    
  private:
    static const LazyCreator lazy_creator;
    static const LazyDestroyer bonus_destroy_notify;
    
    inline static Timer<> existence_timer = { Timer<>::maxInterval() };
    inline static std::atomic<bool> is_tacked = true;
};


#endif //SNAKE_EAT_HPP