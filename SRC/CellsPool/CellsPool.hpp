//
// Created by Lyosha12 on 22.06.2018.
//

#ifndef SNAKE_CELLSPOOL_HPP
#define SNAKE_CELLSPOOL_HPP

#include <mutex>
#include <list>
#include <vector>
#include <SFML/Graphics.hpp>

#include "NotFoundFreeCell/NotFoundFreeCell.hpp"
#include "Cell/Cell.hpp"
#include "Cell/Filler/Filler.hpp"
#include "Utility/ListRunner.hpp"
#include "Utility/TextureStorage/TextureStorage.hpp"
#include "Utility/RandomGenerator/RandomGenerator.hpp"

class DefaultRectangle;
class TextureStorage;

class CellsPool: public sf::Drawable {
    // Класс отвечает за распределение клеток между
    // объектами на поле. Между змейкой, бонусами.
    
    // Это разделяемый ресурс. Прежде, чем обратиться к нему,
    // сначала нужно захватить его мьютекс.
    
    using FillerCreator  = Filler::FillerCreator;
    using FillerUPtr     = Cell::FillerUPtr;
    using CellCPtr       = Cell::CellCPtr  ;
    using CellPtr        = Cell::CellPtr   ;
    using AvailablesIter = std::list<CellCPtr>::const_iterator;
    
  public:
    CellsPool(
        size_t count_cells_x,
        size_t count_cells_y,
        DefaultRectangle const& settings
    );
    
    struct RequestedCell {
        // Бассейн клеток отдаёт этот объект всякому,
        // кто захотел владеть клеткой.
    
        Cell::CellCPtr cell;
        Cell::FillerUPtr prev_filler;
    };
    
    RequestedCell getRandCell(FillerCreator filler_creator);
    RequestedCell getNearCell(CellCPtr target, FillerCreator filler_creator);
    // Запросить клетку по направлению (direction) от заданной.
    RequestedCell getCell(CellCPtr target, Coord direction, FillerCreator filler_creator);
    RequestedCell getCell(Coord coord, FillerCreator filler_creator);
    
    // Выбросить старый заполнитель и создать новый.
    void replaceFiller(CellCPtr target, FillerCreator filler_creator);
    
    // Установить стандартный FreeCell заполнитель.
    void releaseCell(CellCPtr cell_to_release);
  
  public:
    void lock()     const;
    void unlock()   const;
    bool try_lock() const;
  
  private:
    RequestedCell replaceFiller(CellPtr target, FillerUPtr new_filler);
    RequestedCell kickFromAvailable(AvailablesIter target, FillerUPtr new_filler);
    
    Coord normalize(Coord coord) const;
    CellPtr extractCell(Coord coord);
    AvailablesIter findInAvailable(CellCPtr cell);
    
    FillerUPtr createFreeFiller(Coord coord) const;
    
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
};


#endif //SNAKE_CELLSPOOL_HPP
