//
// Created by Lyosha12 on 24.06.2018.
//

#ifndef SNAKE_FILLER_HPP
#define SNAKE_FILLER_HPP

#include <SFML/Graphics.hpp>

#include "../../../Coord/Coord.hpp"
#include "../../DefaultRectangle/DefaultRectangle.hpp"

class Snake;
class Filler: public sf::Drawable {
    // Заполнитель клетки - это некий спрайт.
    // Его текстуру и форму определяет наследник этого класса.
    
    // Так как заполнитель может быть пуст,
    // то вызывать не подумав modify нельзя.
    // Это контролирует вспомогательный класс RequestedCell.
  
  public:
    Filler(DefaultRectangle const& default_rectangle,
           Coord const& coord,
           sf::Texture const& texture,
           bool is_usable
    );
    
    virtual ~Filler() = default;
    
    // Каждую клетку змейка может занять.
    // И, в зависимости от реализации функции modify,
    // змейка будет изменена так или иначе.
    virtual void modify(Snake&) const;
  
    // Служит для формирования списка свободных клеток.
    bool isUsable() const;
    
  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Sprite sprite;
    bool is_usable;
};

#endif //SNAKE_FILLER_HPP
