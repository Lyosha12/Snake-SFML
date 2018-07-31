//
// Created by Lyosha12 on 25.06.2018.
//

#ifndef SNAKE_STEPPEDONHEAD_HPP
#define SNAKE_STEPPEDONHEAD_HPP

#include "BonusManager/Bonus/Bonus.hpp"

class SteppedOnHead: public Bonus {
    // Делает что-то, если змейка взяла блок головы (чужой змейки, конечно).
    
  public:
    using Bonus::Bonus;
    
    bool activate() override;
    
    static LazyCreator const& getBonusCreator();
    static LazyDestroyer const& getBonusDestroyer();
    
  private:
    static const LazyCreator lazy_creator;
    static const Bonus::LazyDestroyer bonus_destroy_notify;
};


#endif //SNAKE_STEPPEDONHEAD_HPP
