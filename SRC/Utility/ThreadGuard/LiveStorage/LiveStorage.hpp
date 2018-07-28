//
// Created by Lyosha12 on 26.06.2018.
//

#ifndef SNAKE_THREADLIVESTORAGE_HPP
#define SNAKE_THREADLIVESTORAGE_HPP


#include <atomic>

class LiveStorage {
    // Контролирует работу потока, хранящего этот класс.
    // Cancellation token в соответствии с
    // https://habr.com/post/306332/
    
  public:
    LiveStorage(bool is_alive);
    LiveStorage(LiveStorage const&) = delete;
    LiveStorage& operator= (LiveStorage const&) = delete;
    LiveStorage& operator= (bool value);
    
    operator bool() const;
  
  private:
    std::atomic<bool> is_alive;
};


#endif //SNAKE_THREADLIVESTORAGE_HPP
