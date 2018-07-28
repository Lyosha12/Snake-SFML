//
// Created by Lyosha12 on 23.06.2018.
//

#ifndef SNAKE_BONUS_HPP
#define SNAKE_BONUS_HPP

#include <memory>
#include <functional>

class Snake;


class Bonus {
    /* Бонус - это некоторое действие над змейкой.
     * Бонус связан с заполнителем клетки.
     * Сначала создаётся заполнитель клетки.
     * В процессе создания с заполнителем ассоциируется бонус
     * посредством функций типа LazyCreator и LazyDestroyer.
     * Какой бонус ассоциировать - решает заполнитель.
     */
    
  public:
    Bonus(Snake& snake);
    virtual ~Bonus() = default;
    Bonus(Bonus const&) = delete;
    Bonus& operator= (Bonus const&) = delete;
    
    virtual bool activate() = 0;
    
    /* Функции отложенного создания и удаления бонуса.
     * Каждый заполнитель ассоциируется с ними.
     *
     * Когда из класса-потомка Bonus будет возвращена функция LazyCreator,
     * можно считать, что бонус начал своё существование на поле.
     * Бонус считается взятым, если вызывается LazyCreator.
     *
     * LazyDestroyer нужна, в основном, для оповещения
     * соответствующего класса-потомка Bonus о том, что заполнитель, хранящий
     * LazyCreator, уничтожен, из-за чего бонус невозможно взять и он считается
     * не не существующим на поле.
     */
    using LazyCreator = std::function<std::unique_ptr<Bonus>(Snake&)>;
    using LazyDestroyer = std::function<void(void)>;
    
  protected:
    Snake& snake;
};


#endif //SNAKE_BONUS_HPP
