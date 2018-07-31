//
// Created by Lyosha12 on 28.07.2018.
//

#include <random>
#include <chrono>

#include "RandomGenerator.hpp"

thread_local std::minstd_rand0 generator (
    // Инициализируем уникальным временем.
    static_cast<unsigned>(
        std::chrono::system_clock::now().time_since_epoch().count()
    )
);

thread_local std::random_device random_device;
size_t random() {
    return generator();
}