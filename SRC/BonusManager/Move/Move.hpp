//
// Created by Lyosha12 on 25.06.2018.
//

#ifndef SNAKE_MOVE_HPP
#define SNAKE_MOVE_HPP

#include "BonusManager/Bonus/Bonus.hpp"

class Move: public Bonus {
    // По задумке, бонус движения хранит каждая свободная клетка.
    
  public:
    Move(Snake& snake);
    
    bool activate() override;
    
    static LazyCreator const& getBonusCreator();
    static LazyDestroyer const& getBonusDestroyer();
    
  private:
    static const LazyCreator lazy_creator;
    static const LazyDestroyer bonus_destroy_notify;
};


#endif //SNAKE_MOVE_HPP
