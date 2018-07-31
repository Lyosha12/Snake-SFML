//
// Created by Lyosha12 on 25.06.2018.
//

#ifndef SNAKE_STEPPEDONBODY_HPP
#define SNAKE_STEPPEDONBODY_HPP


#include "BonusManager/Bonus/Bonus.hpp"

class SteppedOnBody: public Bonus {
    // Делает что-то, если змейка взяла блок своего тела (или чужого).
    
  public:
    using Bonus::Bonus;
    
    bool activate() override;
    
    static LazyCreator const& getBonusCreator();
    static LazyDestroyer const& getBonusDestroyer();
    
  private:
    static const LazyCreator lazy_creator;
    static const LazyDestroyer bonus_destroy_notify;
};


#endif //SNAKE_STEPPEDONBODY_HPP
