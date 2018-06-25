//
// Created by Lyosha12 on 24.06.2018.
//

#ifndef SNAKE_FILLER_HPP
#define SNAKE_FILLER_HPP

#include <functional>
#include <SFML/Graphics.hpp>

#include "../../../Coord/Coord.hpp"
#include "../../DefaultRectangle/DefaultRectangle.hpp"
#include "../../../BonusManager/Bonus/Bonus.hpp"

class Snake;
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
    
    // Задаётся BonusManager'ом.
    std::function<std::unique_ptr<Bonus>(Snake&)> bonus_creator;
};

#endif //SNAKE_FILLER_HPP
