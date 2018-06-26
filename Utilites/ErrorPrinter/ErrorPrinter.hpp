//
// Created by Lyosha12 on 18.06.2018.
//

#ifndef SNAKE_ERRORPRINTER_HPP
#define SNAKE_ERRORPRINTER_HPP

#include <string>
#include <mutex>

class ErrorPrinter {
    // Реализует обработку фатального исключения.
    
  public:
    ErrorPrinter(std::string cause);
    void print();
  
  private:
    std::string cause;
    std::mutex error_mutex;
};


#endif //SNAKE_ERRORPRINTER_HPP
