// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 26.06.2018.
//

#include "LiveStorage.hpp"

LiveStorage::LiveStorage(bool is_alive): is_alive(is_alive) { }
LiveStorage::operator bool() const {
    return is_alive;
}
LiveStorage& LiveStorage::operator= (bool value) {
    is_alive = value;
    return *this;
}