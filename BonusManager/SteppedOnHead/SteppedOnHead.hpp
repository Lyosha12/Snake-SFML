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
    
    inline static const
    std::function<std::unique_ptr<Bonus>(Snake&)>
    lazy_creator = [] (Snake& snake) {
        return new SteppedOnHead(snake);
    };
};


#endif //SNAKE_STEPPEDONHEAD_HPP
