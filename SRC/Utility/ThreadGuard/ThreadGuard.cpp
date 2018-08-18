// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 26.06.2018.
//

#include "ThreadGuard.hpp"

ThreadGuard::~ThreadGuard() {
    if(thread.joinable()) {
        alive = false;
        thread.join();
    }
}
