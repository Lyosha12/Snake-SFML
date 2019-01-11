//
// Created by Lyosha12 on 28.07.2018.
//

#ifndef SNAKE_GAMEEND_HPP
#define SNAKE_GAMEEND_HPP

#include <stdexcept>

class EndGame: public std::runtime_error {
  public:
    using std::runtime_error::runtime_error;
};


#endif //SNAKE_GAMEEND_HPP
