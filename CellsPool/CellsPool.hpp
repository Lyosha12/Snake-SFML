//
// Created by Lyosha12 on 22.06.2018.
//

#ifndef SNAKE_CELLSPOOL_HPP
#define SNAKE_CELLSPOOL_HPP

#include <mutex>
#include <list>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Cell/Cell.hpp"
#include "NotFoundFreeCell/NotFoundFreeCell.hpp"
#include "../Utilites/ListRunner.hpp"
#include "Cell/Filler/Filler.hpp"
#include "../Utilites/TextureStorage/TextureStorage.hpp"

class DefaultRectangle;
class TextureStorage;

class CellsPool: public sf::Drawable {
    // Класс отвечает за распределение клеток между
    // объектами на поле. Между змейкой, бонусами.
    
    // Это разделяемый ресурс. Прежде, чем обратиться к нему,
    // сначала нужно захватить его мьютекс.
    
    using FillerUPtr   = Cell::FillerUPtr;
    using CellCPtr     = Cell::CellCPtr  ;
    using CellPtr      = Cell::CellPtr   ;
    using AvailablesIter = std::list<CellCPtr>::const_iterator;
    
  public:
    CellsPool(
        size_t count_cells_x,
        size_t count_cells_y,
        sf::RenderWindow& window,
        DefaultRectangle const& settings
    );
    
    struct RequestedCell {
        // Бассейн клеток отдаёт этот объект всякий раз,
        // когда кто-то завладеет клеткой.
    
        Cell::CellCPtr cell;
        Cell::FillerUPtr prev_filler;
    };
    
    template <class IncomingFiller>
    RequestedCell getRandCell();
    template <class IncomingFiller>
    RequestedCell getNearCell(CellCPtr target);
    template <class IncomingFiller> // Клетка, по направлению от заданной.
    RequestedCell getCell(CellCPtr target, Coord direction);
    
    // Выбросить старый заполнитель и создать новый.
    template <class IncomingFiller>
    void replaceFiller(CellCPtr target);
    
    void releaseCell(CellCPtr& cell_to_release);
  
  public:
    void lock()     const;
    void unlock()   const;
    bool try_lock() const;
  
  private:
    template <class IncomingFiller>
    std::unique_ptr<Filler> fillerCreator(Coord const& sprite_location) const;
    RequestedCell replaceFiller(CellPtr target, FillerUPtr new_filler);
    RequestedCell kickFromAvailable(AvailablesIter target, FillerUPtr new_filler);
    
    Coord normalize(Coord coord) const;
    CellPtr extractCell(Coord coord);
    AvailablesIter findInAvailable(CellCPtr cell);
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
  private:
    // Задаётся при старте программы и хранится в меню.
    DefaultRectangle const& default_rectangle;
    size_t count_cells_x;
    size_t count_cells_y;
    
    std::vector<std::vector<Cell>> cells;
    mutable std::mutex cells_mutex;
    // Из этого списка раздаются указатели на клетки
    // для учёта их другими сущностями.
    // Изменять их может только внутренняя реализация
    // бассейна клеток - через const_cast<CellPtr>.
    std::list<CellCPtr> available_cells;
    
    TextureStorage background_texture;
    sf::Sprite background;
    
    sf::RenderWindow& window;
};

#include "CellsPool.tpl.cpp"


#endif //SNAKE_CELLSPOOL_HPP
