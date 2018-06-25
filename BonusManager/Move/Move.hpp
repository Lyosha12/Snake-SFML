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
    
    static const LazyCreator lazy_creator;
};


#endif //SNAKE_MOVE_HPP
