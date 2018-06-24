//
// Created by Lyosha12 on 24.06.2018.
//

#ifndef SNAKE_FILLER_HPP
#define SNAKE_FILLER_HPP

#include <SFML/Graphics.hpp>

#include "../../../Coord/Coord.hpp"
#include "../../DefaultRectangle/DefaultRectangle.hpp"


// FIXME: Временно голова и тело выполняют одну и ту же операцию
// При попытке взять их игра завершиться.
// Для мультиплеера нужно расширить идею.
void endGame();

class Snake;
class Filler: public sf::Drawable {
    // Заполнитель клетки - это некий спрайт.
    // Его текстуру и форму определяет наследник этого класса.
  
  public:
    Filler(DefaultRectangle const& default_rectangle,
           Coord const& coord,
           sf::Texture const& texture,
           bool is_free = false
    );
    
    virtual ~Filler() = default;
    
    // Каждую клетку змейка может занять.
    // И, в зависимости от реализации функции modify,
    // змейка будет изменена так или иначе.
    virtual void modify(Snake&) const;
    
    bool isFree() const;
    
  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Sprite sprite;
    bool const is_free;
};

#endif //SNAKE_FILLER_HPP
