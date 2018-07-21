//
// Created by Lyosha12 on 24.06.2018.
//

#ifndef SNAKE_FILLER_HPP
#define SNAKE_FILLER_HPP

#include <functional>

#include <SFML/Graphics.hpp>
#include "../../../BonusManager/Bonus/Bonus.hpp"
#include "../../../Utilites/Timer.hpp"

class Snake;
class DefaultRectangle;
class Coord;

class Filler: public sf::Drawable {
    /*
      * Заполнитель клетки - это некий спрайт.
        Его текстуру и форму определяет наследник этого класса.
      * Кроме того, что это спрайт, заполнитель ещё определяет доступность
        клетки: можно ли её посетить (CanBeTake). Например, чтобы клетку
        змейки одного игрока не забрал другой без "последствий".
    */
  
  protected:
    enum class CanBeTake {
        Yes, No
    };
    
  public:
    Filler(DefaultRectangle const& default_rectangle,
           Coord const& coord,
           sf::Texture const& texture,
           Bonus::LazyCreator const& bonus_creator,
           Bonus::LazyDestroyer const& bonus_destroy_notify,
           CanBeTake can_be_take
    );
    
    virtual ~Filler();
    
    // Клетку змейка может занять - тогда ей будет
    // возвращён сконструированный бонус, за который отвечает BonusManager.
    //
    // При такой организации любой заполнитель может содержать любой бонус.
    // Вряд ли потребуется показывать еду как барьер, хотя в последствии
    // можно было бы определить массив бонусов на конкретной клетке.
    std::unique_ptr<Bonus> getBonus(Snake&) const;
    
    // Можно ли этой (или любой другой) змейке
    // занять клетку с таким заполнителем.
    bool isCanBeTake() const;
  
    
  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Sprite sprite;
    
    // Задаётся каждым бонусом отдельно.
    // Отвечает за отложенное создание бонуса в стиле RAII.
    Bonus::LazyCreator bonus_creator;
    Bonus::LazyDestroyer const& bonus_destroy_notify;
    
    CanBeTake const can_be_take;
};

#endif //SNAKE_FILLER_HPP
