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
    // объектами на поле. Между змейкой,
    // бонусами и другими сущностями типа барьеров.
    
    // Это разделяемый ресурс. Прежде, чем обратиться к нему,
    // сначала нужно захватить его мьютекс.
    
    using FillerUPtr   = Cell::FillerUPtr;
    using CellCPtr     = Cell::CellCPtr  ;
    using CellPtr      = Cell::CellPtr   ;
    using AviablesIter = std::list<CellCPtr>::const_iterator;
    
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
    RequestedCell getRandCell() {
        // Выбрав случайно число по размеру списка свободных клеток,
        // вернём результирующую клетку, удалив её из доступных.
        
        if(available_cells.empty()) {
            throw NotFoundFreeCell({}, "rand free cell not exist");
        }
        
        size_t rand_cell = std::rand()%available_cells.size();
        AviablesIter requested_cell = getListElement(available_cells, rand_cell);
    
        std::unique_ptr<Filler> new_filler = fillerCreator<IncomingFiller>(
            (*requested_cell)->coord
        );
        return kickFromAvailable(requested_cell, std::move(new_filler));
    }
    template <class IncomingFiller>
    RequestedCell getNearCell(CellCPtr target) {
        // Берём случайную свободную клетку в радиусе одной от заданной.
        
        // Найдём её соседей
        CellCPtr up    = extractCell(target->coord + Coord{ 0, -1});
        CellCPtr down  = extractCell(target->coord + Coord{ 0,  1});
        CellCPtr right = extractCell(target->coord + Coord{ 1,  0});
        CellCPtr left  = extractCell(target->coord + Coord{-1,  0});
        std::vector<CellCPtr> neighbors = {up, down, right, left};
        
        // Выберем случайную клетку...
        while(!neighbors.empty()) {
            size_t rand_neighbor = std::rand()%neighbors.size();
            CellCPtr neighbor = neighbors[rand_neighbor];
            
            // ... доступную к использованию.
            if(neighbor->filler->isFree()) {
                std::unique_ptr<Filler> new_filler = fillerCreator<IncomingFiller>(
                    neighbor->coord
                );
                return kickFromAvailable(findInAvailable(neighbor), std::move(new_filler));
            } else
                neighbors.erase(neighbors.begin() + rand_neighbor);
        }
        
        throw NotFoundFreeCell(target, "near free cell not exist");
    }
    template <class IncomingFiller>
    RequestedCell getCell(CellCPtr target, Coord direction) {
        // Возьмём клетку по заданному направлению относительно текущей.
        CellPtr requested_cell = extractCell(target->coord + direction);
        
        std::unique_ptr<Filler> new_filler = fillerCreator<IncomingFiller>(
            requested_cell->coord
        );

        try {
            return kickFromAvailable(
                findInAvailable(requested_cell),
                std::move(new_filler)
            );
        } catch(NotFoundFreeCell& e) {
            // Часть геймплея: клетка может быть занятой -
            // всё равно вернём её, но её заполнитель трогать не нужно.
            return { requested_cell, nullptr };
        }
    }
    
    void releaseCell(CellCPtr& cell_to_release);
  
  public:
    void lock()     const;
    void unlock()   const;
    bool try_lock() const;
  
  private:
    template <class IncomingFiller>
    std::unique_ptr<Filler> fillerCreator(Coord const& sprite_location) const {
        return std::unique_ptr<Filler>(
            new IncomingFiller(
                default_rectangle, sprite_location,
                IncomingFiller::BonusType::getBonusCreator()
            )
        );
    }
    RequestedCell kickFromAvailable(AviablesIter runner, FillerUPtr new_filler);
    Coord normalize(Coord coord) const;
    CellPtr extractCell(Coord coord);
    AviablesIter findInAvailable(CellCPtr cell);
    
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




#endif //SNAKE_CELLSPOOL_HPP
