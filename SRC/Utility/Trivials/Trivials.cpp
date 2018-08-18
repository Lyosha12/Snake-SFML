// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 18.08.2018.
//

#include "Trivials.hpp"


int sign(int value) {
    return value > 0 ? 1 : value < 0 ? -1 : 0;
}