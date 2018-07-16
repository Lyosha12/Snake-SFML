//
// Created by Lyosha12 on 23.06.2018.
//

#ifndef SNAKE_EAT_HPP
#define SNAKE_EAT_HPP

#include <atomic>
#include "../Bonus/Bonus.hpp"
#include "../../Utilites/ThreadGuard/LiveStorage/LiveStorage.hpp"

class Eat: public Bonus {
  public:
    Eat(Snake& snake);
    
    bool activate() override;
    static bool isExists();
    
    static LazyCreator const& getBonusCreator();
    static LazyDestroyer const& getBonusDestroyer();
    
  private:
    inline static LiveStorage is_exist = false;
    static const LazyCreator lazy_creator;
    static const LazyDestroyer bonus_destroy_notify;
};


#endif //SNAKE_EAT_HPP
