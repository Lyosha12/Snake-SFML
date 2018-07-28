//
// Created by Lyosha12 on 30.04.2018.
//

#ifndef LYOSHA12_TIMER_HPP
#define LYOSHA12_TIMER_HPP

#include <stdexcept>
#include <iostream>
#include <chrono>
using namespace std::chrono_literals;

template <class Clock = std::chrono::steady_clock>
class Timer {
    /* Классу задаётся некоторый интервал времени,
     * после чего вызывающая сторона проверяет не прошёл ли он.
     * Как только интервал прошёл, точкой отсчёта нового становится время,
     * когда была вызвана последняя проверка.
     */
  public:
    using InternalTimeUnit = std::chrono::nanoseconds;
    
  public:
    template <class IncomingTimeUnit = InternalTimeUnit>
    Timer(IncomingTimeUnit interval = IncomingTimeUnit(0))
    : interval(convert(interval))
    { }
    
    template <class IncomingTimeUnit, class IntegralT>
    void             setInterval(IntegralT interval)       {
        this->interval = convert(IncomingTimeUnit(interval));
    }
    InternalTimeUnit getInterval(                         ) const {
        return interval;
    }
    bool             isIntervalExpire()                     const {
        if(interval == InternalTimeUnit(0)) {
            std::cerr << "Warning: check to expire zero interval\n";
        }
        
        if(is_paused) {
            std::cerr << "Trying to check Timer when it has paused.";
        }
        
        return Clock::now() - last_moment > interval;
    }

    
    void reset() {
        last_moment = Clock::now();
    }
    void pause() {
        residual_interval = Clock::now() - last_moment;
        is_paused = true;
    }
    void resume() {
        last_moment = Clock::now() - residual_interval;
        is_paused = false;
    }
    
    static InternalTimeUnit maxInterval() {
        return InternalTimeUnit::max();
    }
    
  private:
    template <class IncomingTimeUnit>
    InternalTimeUnit convert(IncomingTimeUnit interval) {
        return std::chrono::duration_cast<InternalTimeUnit> (interval);
    }
  
  private:
    typename Clock::time_point last_moment = Clock::now();
    InternalTimeUnit interval;
    
    InternalTimeUnit residual_interval; // Остаток интервала при паузе.
    bool is_paused = false;
};


#endif // LYOSHA12_TIMER_HPP
