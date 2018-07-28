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