//
// Created by Lyosha12 on 23.06.2018.
//

#include "Eat.hpp"
#include "../EatFiller/EatFiller.hpp"

Eat::~Eat() {
    // Согласно RAII, тут бонус прекращает своё существование на поле.
    is_exist = false;
}

bool Eat::activate() {
    // Активация не нужна.
    // Бонус уже "подействовал", не удаляя хвост змейки.
    // Поэтому просто скажем, что в списке активных бонусов он лишний.
    return false;
}

Bonus::LazyCreator const& Eat::getBonusCreator() {
    is_exist = true;
    return lazy_creator;
}

bool Eat::isExists() {
    return is_exist;
}

const Bonus::LazyCreator Eat::lazy_creator = [] (Snake& snake) {
    return std::unique_ptr<Bonus>(new Eat(snake));
};