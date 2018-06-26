//
// Created by Lyosha12 on 24.06.2018.
//

#ifndef SNAKE_FILLER_HPP
#define SNAKE_FILLER_HPP

#include <functional>
#include <SFML/Graphics.hpp>

class Snake;
class DefaultRectangle;
class Bonus;
class Coord;

class Filler: public sf::Drawable {
    // Заполнитель клетки - это некий спрайт.
    // Его текстуру и форму определяет наследник этого класса.
  
  public:
    Filler(DefaultRectangle const& default_rectangle,
           Coord const& coord,
           sf::Texture const& texture,
           bool is_free,
           std::function<std::unique_ptr<Bonus>(Snake&)> bonus_creator
    );
    
    virtual ~Filler() = default;
    
    // Каждую клетку змейка может занять.
    // Змейке будет возвращён сконструированный бонус,
    // за который отвечает BonusManager.
    std::unique_ptr<Bonus> getBonus(Snake&) const;
    
    bool isFree() const;
    
  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Sprite sprite;
    bool const is_free;
    
    // Задаётся каждым бонусом отдельно.
    // Отвечает за отложенное создание бонуса в стиле RAII:
    // Конструктор что-то подготовит для изменений в змейке,
    // функция активации применит бонус, возможно, не один раз.
    // Бонус удалится из активных змейкой, как только активация провалится.
    std::function<std::unique_ptr<Bonus>(Snake&)> bonus_creator;
};

#endif //SNAKE_FILLER_HPP
