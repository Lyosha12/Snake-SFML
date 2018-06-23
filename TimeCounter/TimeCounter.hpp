//
// Created by Lyosha12 on 30.04.2018.
//

#ifndef LAB_3_TIMECONTROLLER_HPP
#define LAB_3_TIMECONTROLLER_HPP

#include <chrono>

template <class ClockType = std::chrono::steady_clock>
class TimeCounter {
  public:
    using IntervalType = std::chrono::nanoseconds;
    
  public:
    template <class IntervalTypeIncoming = std::chrono::seconds>
    TimeCounter(IntervalTypeIncoming interval)
        : interval(std::chrono::duration_cast<IntervalType> (interval))
    { }
    
    bool isIntervalPassed(float interval_multipler = 1) {
        if(is_paused)
            throw std::logic_error("Trying to check TimeCounter when it has paused.");
        
        if(ClockType::now() - last_moment < interval * interval_multipler) {
            return false;
        }
        else {
            last_moment = ClockType::now();
            return true;
        }
    }
    
    
    std::chrono::nanoseconds getInterval() const {
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


#endif //LAB_3_TIMECONTROLLER_HPP
