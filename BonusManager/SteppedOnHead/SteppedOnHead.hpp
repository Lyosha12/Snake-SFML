//
// Created by Lyosha12 on 25.06.2018.
//

#ifndef SNAKE_STEPPEDONHEAD_HPP
#define SNAKE_STEPPEDONHEAD_HPP

#include "../Bonus/Bonus.hpp"

class SteppedOnHead: public Bonus {
  public:
    SteppedOnHead(Snake& snake);
    bool activate() override;
    
    static LazyCreator const& getBonusCreator();
    static LazyDestroyer const& getBonusDestroyer();
    
  private:
    static const LazyCreator lazy_creator;
    static const Bonus::LazyDestroyer bonus_destroy_notify;
};


#endif //SNAKE_STEPPEDONHEAD_HPP
