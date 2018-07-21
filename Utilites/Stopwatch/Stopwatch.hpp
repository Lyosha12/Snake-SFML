//
// Created by Lyosha12 on 17.07.2018.
//

#ifndef SNAKE_TIMER_HPP
#define SNAKE_TIMER_HPP

#include <string>
#include <type_traits>
#include <stdexcept>
#include <chrono>
using namespace std::chrono_literals;

template <class Clock = std::chrono::steady_clock>
class Stopwatch {
    /* Всего лишь таймер - сколько прошло времени от и до заданной точки.
     */
    
  public:
    using nanoseconds   = std::chrono::nanoseconds;
    using microseconds  = std::chrono::microseconds;
    using milliseconds  = std::chrono::milliseconds;
    using seconds       = std::chrono::seconds;
    using minutes       = std::chrono::minutes;
    using hours         = std::chrono::hours;
    
  private:
    template <class DurationType>
    struct TimeRepresent {
        TimeRepresent(size_t nanos)
        : count(normalize(nanos))
        { }
    
        static constexpr std::string getTimeName() {
            if constexpr (is_same<DurationType, nanoseconds> ) { return "ns" ; }
            if constexpr (is_same<DurationType, microseconds>) { return "mcs"; }
            if constexpr (is_same<DurationType, milliseconds>) { return "ms" ; }
            if constexpr (is_same<DurationType, seconds>     ) { return "s"  ; }
            if constexpr (is_same<DurationType, minutes>     ) { return "m"  ; }
            if constexpr (is_same<DurationType, hours>       ) { return "h"  ; }
            
            throw std::logic_error("Unexpected time type");
        }
        
        static constexpr size_t normalize(size_t nanos) {
            size_t rest = 0;
            
            rest = nanos % 1000; // Count nanoseconds;
            if(is_same<DurationType, nanoseconds> ) return rest;
            
            rest = (nanos /= 1000) % 1000; // Count microseconds;
            if(is_same<DurationType, microseconds>) return rest;
            
            rest = (nanos /= 1000) % 1000; // Count milliseconds;
            if(is_same<DurationType, milliseconds>) return rest;
            
            rest = (nanos /= 1000) % 60  ; // Count seconds;
            if(is_same<DurationType, seconds>     ) return rest;
            
            rest = (nanos /= 60) % 60  ; // Count minutes;
            if(is_same<DurationType, minutes>     ) return rest;
            
            rest = (nanos /= 60) % 24  ; // Count hours;
            if(is_same<DurationType, hours>       ) return rest;
            
            
            throw std::logic_error("Requested time type is not a time");
        }
    
        size_t count;
        bool is_use_in_represent = count != 0;
        std::string time_name = getTimeName();
        
        operator std::string () const {
            if(is_use_in_represent)
                return std::to_string(count) + time_name + " ";
            else
                return "";
        }
        
      private:
        template <class A, class B>
        inline static bool constexpr is_same = std::is_same<A, B>::value;
    };
  
  public:
    void run() {
        start = Clock::now();
        finish = { };
    }
    
    void stop() {
        finish = Clock::now();
    }
    
    template <class TimeType>
    size_t getInterval() const {
        return std::chrono::duration_cast<TimeType>(finish - start).count();
    }
    std::string getFullInterval() {
        TimeRepresent<nanoseconds > nanos  (getInterval<nanoseconds>());
        TimeRepresent<microseconds> micros (getInterval<nanoseconds>());
        TimeRepresent<milliseconds> millis (getInterval<nanoseconds>());
        TimeRepresent<seconds     > seconds(getInterval<nanoseconds>());
        TimeRepresent<minutes     > minutes(getInterval<nanoseconds>());
        TimeRepresent<hours       > hours  (getInterval<nanoseconds>());
        
        return
            std::string(nanos   ) +
            std::string(micros  ) +
            std::string(millis  ) +
            std::string(seconds ) +
            std::string(minutes ) +
            std::string(hours   ) ;
    }
    
  private:
    std::chrono::time_point<Clock, nanoseconds> start;
    std::chrono::time_point<Clock, nanoseconds> finish;
};


#endif //SNAKE_TIMER_HPP
