//
// Created by Lyosha12 on 30.04.2018.
//

#ifndef LAB_3_TIMECONTROLLER_HPP
#define LAB_3_TIMECONTROLLER_HPP

#include <chrono>

template <class ClockType = std::chrono::steady_clock>
class TimeCounter {
  public:
    template <class IntervalType = std::chrono::seconds>
    TimeCounter(IntervalType interval)
        : interval(std::chrono::duration_cast<std::chrono::nanoseconds> (interval))
    { }
    
    bool isIntervalPassed(int interval_multipler = 1) {
        if(ClockType::now() - last_moment < interval*interval_multipler) {
            return false;
        }
        else {
            last_moment = ClockType::now();
            return true;
        }
    }
    
  private:
    typename ClockType::time_point last_moment = ClockType::now();
    std::chrono::nanoseconds interval;
  
};


#endif //LAB_3_TIMECONTROLLER_HPP
