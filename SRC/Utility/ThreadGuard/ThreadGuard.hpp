//
// Created by Lyosha12 on 26.06.2018.
//

#ifndef SNAKE_THREADGUARD_HPP
#define SNAKE_THREADGUARD_HPP

#include <thread>
#include <mutex>
#include <atomic>

#include "LiveStorage/LiveStorage.hpp"

class ThreadGuard {
    // RAII-обёртка над стандартным потоком.
    // В соответствии с https://habr.com/post/306332/
    
  public:
    template <class Function, class... Params>
    ThreadGuard(Function&& function, Params&&... args)
    : thread(function, std::ref(live_controller), std::forward<Params>(args)...)
    { }
    
    ~ThreadGuard();
    
  private:
    std::thread thread;
    LiveStorage live_controller = true;
};

#endif //SNAKE_THREADGUARD_HPP
