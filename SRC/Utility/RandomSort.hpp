//
// Created by Lyosha12 on 28.07.2018.
//

#ifndef SNAKE_RANDOMSORT_HPP
#define SNAKE_RANDOMSORT_HPP


#include <Utility/RandomGenerator/RandomGenerator.hpp>

template <class Container>
void randomSort(Container& container) {
    std::sort(std::begin(container), std::end(container), [] (auto, auto) {
        return random() % 2;
    });
}

#endif //SNAKE_RANDOMSORT_HPP
