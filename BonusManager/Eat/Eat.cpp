//
// Created by Lyosha12 on 23.06.2018.
//

#include "Eat.hpp"
#include "../EatFiller/EatFiller.hpp"

// При взятии бонуса Eat, в отличии от бонуса Move,
// хвостовая клетка змейки не удаляется.
// По сути, выполняем полезную работу без лишнего кода.

Eat::Eat(Snake& snake): Bonus(snake) {
    // Пусть на поле будет только один бонус Eat,
    // пока нет реализации мультиплеера.
    is_exist = true;
}
Eat::~Eat() {
    // Согласно RAII, тут бонус прекращает своё существование на поле.
    is_exist = false;
}

bool Eat::activate() {
    // Активация как бы и не нужна.
    // Бонус уже "подействовал", не удаляя хвост змейки.
    // Поэтому просто скажем, что в списке активных бонусов он лишний.
    return false;
}

bool Eat::isExists() {
    return is_exist;
}

const Bonus::LazyCreator Eat::lazy_creator = [] (Snake& snake) {
    return std::unique_ptr<Bonus>(new Eat(snake));
};