//
// Created by Lyosha12 on 17.07.2018.
//

#ifndef SNAKE_TIMEPROFILER_HPP
#define SNAKE_TIMEPROFILER_HPP

#include <iostream>
#include "../Timer/Timer.hpp"

#define START_TIME_PROFILER(what_testing) \
std::string explanation = what_testing; \
Timer<> timer; \
timer.run(); \

#define STOP_TIME_PROFILER \
timer.stop(); \
std::cout << "Time for \"" << explanation << "\": " \
<< timer.getFullInterval() << std::endl;



#endif //SNAKE_TIMEPROFILER_HPP
