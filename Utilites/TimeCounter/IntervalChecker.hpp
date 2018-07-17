//
// Created by Lyosha12 on 30.04.2018.
//

#ifndef LYOSHA12_INTERVALCHECKER_HPP
#define LYOSHA12_INTERVALCHECKER_HPP

#include <chrono>
#include <stdexcept>

template <class ClockType = std::chrono::steady_clock>
class IntervalChecker {
    /* Классу задаётся некоторый интервал времени,
     * после чего вызывающая сторона проверяет не прошёл ли он.
     * Как только интервал прошёл, точкой отсчёта нового становится время,
     * когда была вызвана последняя проверка.
     */
  public:
    using IntervalType = std::chrono::nanoseconds;
    
  public:
    template <class IntervalTypeIncoming>
    IntervalChecker(IntervalTypeIncoming interval)
    : interval(std::chrono::duration_cast<IntervalType> (interval))
    { }
    
    bool isIntervalPassed(float interval_multipler = 1) {
        if(is_paused)
            throw std::logic_error("Trying to check IntervalChecker when it has paused.");
        
        if(ClockType::now() - last_moment < interval * interval_multipler) {
            return false;
        }
        else {
            last_moment = ClockType::now();
            return true;
        }
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
    
  private:
    typename ClockType::time_point last_moment = ClockType::now();
    IntervalType interval;
    
    IntervalType residual_interval; // Остаток интервала при паузе.
    bool is_paused = false;
};


#endif // LYOSHA12_INTERVALCHECKER_HPP
