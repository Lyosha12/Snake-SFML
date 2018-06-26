//
// Created by Lyosha12 on 25.06.2018.
//

#ifndef SNAKE_STEPPEDONBODY_HPP
#define SNAKE_STEPPEDONBODY_HPP


#include "../Bonus/Bonus.hpp"

class SteppedOnBody: public Bonus {
  public:
    SteppedOnBody(Snake& snake);
    bool activate() override;
    
    // Обратившись к этой функции, можно считать, что бонус начал существовать.
    static LazyCreator const& getBonusCreator();
    
  private:
    static const LazyCreator lazy_creator;
};


#endif //SNAKE_STEPPEDONBODY_HPP
