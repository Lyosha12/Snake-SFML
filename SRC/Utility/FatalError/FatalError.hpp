//
// Created by Lyosha12 on 18.06.2018.
//

#ifndef SNAKE_ERRORPRINTER_HPP
#define SNAKE_ERRORPRINTER_HPP

#include <string>

class FatalError {
    // Реализует обработку фатального исключения.
    
  public:
    FatalError(std::string cause);
    void print();
  
  private:
    std::string cause;
};


#endif //SNAKE_ERRORPRINTER_HPP
