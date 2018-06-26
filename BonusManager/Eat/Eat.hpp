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
    using Bonus::Bonus;
    
    ~Eat();
    bool activate() override;
    static bool isExists();
    
    // Обратившись к этой функции, можно считать, что бонус начал существовать.
    static LazyCreator const& getBonusCreator();
    
  private:
    inline static LiveStorage is_exist = false;
    static const LazyCreator lazy_creator;
};


#endif //SNAKE_EAT_HPP
