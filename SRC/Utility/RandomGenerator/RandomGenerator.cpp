// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 28.07.2018.
//

#include <random>
#include <chrono>

#include "RandomGenerator.hpp"

thread_local std::minstd_rand0 generator (
    // Инициализируем уникальным временем.
    static_cast<unsigned>(
    #ifdef NDEBUG
        std::chrono::system_clock::now().time_since_epoch().count()
    #else
        0
    #endif
    )
);

size_t random() {
    return generator();
}