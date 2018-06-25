//
// Created by Lyosha12 on 25.06.2018.
//

#ifndef SNAKE_MOVE_HPP
#define SNAKE_MOVE_HPP

#include "../Bonus/Bonus.hpp"

class Move: public Bonus {
  public:
    Move(Snake& snake);
    bool activate() override;
    
    inline static const
    std::function<std::unique_ptr<Bonus>(Snake&)>
    lazy_creator = [] (Snake& snake) {
        return new Move(snake);
    };
};


#endif //SNAKE_MOVE_HPP
