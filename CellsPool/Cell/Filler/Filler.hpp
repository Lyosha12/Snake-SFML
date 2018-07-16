//
// Created by Lyosha12 on 24.06.2018.
//

#ifndef SNAKE_FILLER_HPP
#define SNAKE_FILLER_HPP

#include <functional>
#include <SFML/Graphics.hpp>
#include "../../../BonusManager/Bonus/Bonus.hpp"

class Snake;
class DefaultRectangle;
class Coord;

class Filler: public sf::Drawable {
    /*
      * Заполнитель клетки - это некий спрайт.
        Его текстуру и форму определяет наследник этого класса.
      * Кроме того, что это спрайт, заполнитель ещё определяет доступность
        клетки: можно ли её посетить (CanBeTake). Это нужно для того, чтобы
        бассейн клеток вдруг не забрал заполнитель, скажем, у
        блока змейки другого игрока.
      * Заполнитель - читай бонус - также имеет время своего существования.
      * Если оно прекращается, то он косвенно уведомит об этом BonusManager
      * вызовом bonus_destroy_notify.
    */
  
  protected:
    enum class CanBeTake {
        Yes, No
    };
    
  public:
    Filler(DefaultRectangle const& default_rectangle,
           Coord const& coord,
           sf::Texture const& texture,
           CanBeTake can_be_take,
           Bonus::LazyCreator const& bonus_creator,
           Bonus::LazyDestroyer const& bonus_destroy_notify
    );
    
    virtual ~Filler();
    
    // Клетку змейка может занять, тогда ей будет
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
    CanBeTake const can_be_take;
    
    // Задаётся каждым бонусом отдельно.
    // Отвечает за отложенное создание бонуса в стиле RAII.
    Bonus::LazyCreator bonus_creator;
    Bonus::LazyDestroyer const& bonus_destroy_notify;
};

#endif //SNAKE_FILLER_HPP
