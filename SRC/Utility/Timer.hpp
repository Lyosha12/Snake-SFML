//
// Created by Lyosha12 on 30.04.2018.
//

#ifndef LYOSHA12_TIMER_HPP
#define LYOSHA12_TIMER_HPP

#include <stdexcept>
#include <iostream>
#include <chrono>
using namespace std::chrono_literals;

template <class ClockType = std::chrono::steady_clock>
class Timer {
    /* Классу задаётся некоторый интервал времени,
     * после чего вызывающая сторона проверяет не прошёл ли он.
     * Как только интервал прошёл, точкой отсчёта нового становится время,
     * когда была вызвана последняя проверка.
     */
  public:
    using IntervalType = std::chrono::nanoseconds;
    
  public:
    template <class IntervalTypeIncoming = IntervalType>
    Timer(IntervalTypeIncoming interval = IntervalTypeIncoming(0))
    : interval(std::chrono::duration_cast<IntervalType> (interval))
    { }
    
    bool isIntervalExpire() const {
        if(interval == IntervalType(0)) {
            std::cerr << "Warning: check to expire zero interval\n";
        }
        
        if(is_paused) {
            std::cerr << "Trying to check Timer when it has paused.";
        }
    
        return ClockType::now() - last_moment > interval;
    }
    
    void reset() {
        last_moment = ClockType::now();
    }
    
    
    IntervalType getInterval() const {
        return interval;
    }
    void setInterval(IntervalType interval) {
        this->interval = interval;
    }
    
    void pause() {
        residual_interval = ClockType::now() - last_moment;
        is_paused = true;
    }
    void resume() {
        last_moment = ClockType::now() - residual_interval;
        is_paused = false;
    }
    
    static IntervalType maxInterval() {
        return IntervalType::max();
    }
    
  private:
    typename ClockType::time_point last_moment = ClockType::now();
    IntervalType interval;
    
    IntervalType residual_interval; // Остаток интервала при паузе.
    bool is_paused = false;
};


#endif // LYOSHA12_TIMER_HPP
