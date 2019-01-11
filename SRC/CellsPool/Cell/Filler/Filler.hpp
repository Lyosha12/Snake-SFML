//
// Created by Lyosha12 on 24.06.2018.
//

#ifndef SNAKE_FILLER_HPP
#define SNAKE_FILLER_HPP

#include <functional>

#include <SFML/Graphics.hpp>

#include "CellsPool/DefaultRectangle/DefaultRectangle.hpp"
#include "BonusManager/Bonus/Bonus.hpp"
#include "Utility/Timer.hpp"
#include "Utility/Coord/Coord.hpp"
#include "Utility/TextureStorage/TextureStorage.hpp"

class Snake;

class Filler: public sf::Drawable {
    /* * Заполнитель клетки - это некий спрайт.
         Его текстуру определяет наследник этого класса,
         а форму и расположение - вызывающая сторона.
       * Заполнитель определяет доступность клетки:
         можно ли её посетить (CanBeTake).
         Например, чтобы клетка одного игрока
         вдруг не стала принадлежать другому игроку.
    */
  
  protected:
    enum class CanBeTake {
        Yes, No
    };
    
    
  public:
    using FUP = std::unique_ptr<Filler>;
    using FillerCreator = std::function<FUP(DefaultRectangle const&, Coord)>;
    using SpriteMaker = std::function<sf::Sprite(sf::Texture const&)>;
    
    Filler(
        sf::Sprite sprite,
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
    
    // Можно ли змейке занять клетку с таким заполнителем.
    bool isCanBeTake() const;
    
    // TODO: Слишком сложно
    //  * Не слишком ли часто ходим в кучу при создании заполнителя?
    //  * Может, сделать просто набор заполнителей глобальным?
    //  * Тогда заполнитель будет создаваться быстрее, но добавление
    //  * новых заполнителей будет сопряжено с обновлением глобального списка.
    //  * Или можно подумать о ленивом глобальном списке из заполнителей.
    // Всё это затевалось только для создания спрайта с нужным поворотом
    // из заданной текстуры.
    //
    // * Концентрирует сложность создания заполнителя.
    template <class IncomingFiller>
    static FillerCreator makeFillerCreator(double rotate) {
        // * FillerCreator нужен бассейну клеток.
        // * Это позволяет избавить функции бассейна клеток от шаблонов.
        return [rotate] (DefaultRectangle const& default_rectangle, Coord coord) -> FUP {
            // * Заполнитель создаётся из стандартного прямоугольника и
            //   координаты спрайта. Иногда известно только бассейну клеток.
            return FUP(
                new IncomingFiller(
                    // * Лямбда ниже - это SpriteMaker.
                    // * Спрайт создаётся через call-back
                    //   по известной только заполнителю текстуре.
                    [&] (sf::Texture const& texture) -> sf::Sprite {
                        return default_rectangle.makeSprite(
                            texture,
                            coord,
                            rotate
                        );
                    }
                )
            );
        };
    }
    
  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Sprite sprite;
    
    // Задаётся каждым бонусом отдельно.
    // Отвечает за отложенное создание бонуса в стиле RAII.
    Bonus::LazyCreator const& bonus_creator;
    Bonus::LazyDestroyer const& bonus_destroy_notify;
    
    CanBeTake const can_be_take;
};

#endif //SNAKE_FILLER_HPP
