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
    
    inline static const
    std::function<std::unique_ptr<Bonus>(Snake&)>
    lazy_creator = [] (Snake& snake) {
        return new SteppedOnBody(snake);
    };
};


#endif //SNAKE_STEPPEDONBODY_HPP
