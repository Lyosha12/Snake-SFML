//
// Created by Lyosha12 on 07.08.2018.
//

#ifndef SNAKE_NULLFILLER_HPP
#define SNAKE_NULLFILLER_HPP


#include "CellsPool/Cell/Filler/Filler.hpp"

class NullFiller: public Filler {
    /* Пустой (несуществующий) заполнитель используется,
     * когда сложно определить параметры нужного заполнителя,
     * пока не будет создано несколько таких заполнителей.
     *
     * Наприме, нельзя (или довольно сложно) определить изгиб змейки,
     * т.е. углы поворота спрайтов тела,
     * пока не будут созданы все блоки её тела.
     */
    
    public:
    template <class BonusType = void>
    NullFiller(SpriteMaker sprite_maker)
    : Filler(
        sprite_maker(sf::Texture() /* Пустая */),
        lazy_creator,
        bonus_destroy_notify,
        CanBeTake::No
    )
    { }
    
    
    inline static const Coord orientation = {0, 0}; // Клетке-заглушке - направление-заглушка.
  
  private:
    // Как пограничный случай, не будем создавать отдельный класс
    // для пустого бонуса - не видно пути его применения.
    inline static const Bonus::LazyCreator lazy_creator = [] (Snake&) { return nullptr; };
    inline static const Bonus::LazyDestroyer bonus_destroy_notify = [] { };
};


#endif //SNAKE_NULLFILLER_HPP
