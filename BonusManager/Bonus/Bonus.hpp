//
// Created by Lyosha12 on 23.06.2018.
//

#ifndef SNAKE_BONUS_HPP
#define SNAKE_BONUS_HPP

#include <memory>
#include <functional>

// FIXME: Временно голова и тело выполняют одну и ту же операцию
// При попытке взять их игра завершиться.
// Для мультиплеера нужно расширить идею.
void endGame();

class Snake;
class Bonus {
  public:
    Bonus(Snake& snake);
    virtual ~Bonus() = default;
    Bonus(Bonus const&) = delete;
    Bonus& operator= (Bonus const&) = delete;
    
    virtual bool activate() = 0;
    
    // * Функция отложенного создания бонуса.
    //   Бассейн клеток запрашивает бонус для заполнителя
    //   и передаёт ему только змейку, т.к. только она и нужна бонусу.
    // * Однако, специальные бонусы могут требовать уникальных аргументов
    //   в своём конструкторе. Поэтому каждый бонус реализует эту функцию так,
    //   чтобы его создание на вызывающей стороне прошло только с использованием
    //   одного аргумента - Snake&.
    // * Как только такая функция будет вызвана, можно считать, что бонус
    //   покинул клетку и его нужно освободить.
    using LazyCreator = std::function<std::unique_ptr<Bonus>(Snake&)>;
    
  protected:
    Snake& snake;
    
};


#endif //SNAKE_BONUS_HPP
