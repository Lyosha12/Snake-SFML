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
#include "DefaultRectangle/DefaultRectangle.hpp"
#include "../TextureStorage/TextureStorage.hpp"
#include "RequestedCell/RequestedCell.hpp"
#include "NotFoundFreeCell/NotFoundFreeCell.hpp"

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
    
    template <class Filler>
    RequestedCell getRandCell() {
        if(available_cells.empty()) {
            throw NotFoundFreeCell({}, "rand cell");
        }
        
        size_t i = 0;
        size_t rand_cell = std::rand()%available_cells.size();
        AviablesIter cells_runner = available_cells.begin();
        while(i++ != rand_cell) // Пока не найдём выбранную случайную клетку.
            ++cells_runner;
        
        // Удалим клетку из свободных,
        // если новый её заполнитель недоступен для использования.
        // Вернём клетку и её предыдущий заполнитель.
        std::unique_ptr<Cell::Filler> new_filler(
            // TODO: Почему Filler должен изменять доступность клетки у себя в конструкторе?
            new Filler(default_rectangle, const_cast<Cell&>(**cells_runner))
        );
        return kickFromAvailable(cells_runner, std::move(new_filler));
    }
    template <class Filler>
    RequestedCell getNearCell(CellCPtr target) {
        // Берём случайную клетку в радиусе одной от заданной.
        
        // Найдём её соседей
        CellCPtr up    = extractCell(target->coord + Coord{ 0, -1});
        CellCPtr down  = extractCell(target->coord + Coord{ 0,  1});
        CellCPtr right = extractCell(target->coord + Coord{ 1,  0});
        CellCPtr left  = extractCell(target->coord + Coord{-1,  0});
        std::vector<CellCPtr> neighbors = {up, down, right, left};
        
        // Выберем случайную клетку, доступную к использованию.
        while(!neighbors.empty()) {
            size_t rand_neighbor = std::rand()%neighbors.size();
            CellCPtr neighbor = neighbors[rand_neighbor];
            
            if(neighbor->is_usable) {
                // TODO: Почему Filler должен изменять доступность клетки у себя в конструкторе?
                FillerUPtr new_filler(new Filler(default_rectangle, const_cast<Cell&>(*neighbor)));
                return kickFromAvailable(findInAvailable(neighbor), std::move(new_filler));
        } else
                neighbors.erase(neighbors.begin() + rand_neighbor);
        }
        
        throw NotFoundFreeCell(*target, "near");
    }
    template <class Filler>
    RequestedCell getNearCell(CellCPtr target, Coord direction) {
        // Возьмём клетку по заданному направлению от текущей.
        CellPtr required_cell = extractCell(target->coord + direction);
        
        // TODO: Почему Filler должен изменять доступность клетки у себя в конструкторе?
        std::unique_ptr<Cell::Filler> new_filler(new Filler(default_rectangle, const_cast<Cell&>(*required_cell)));

        return kickFromAvailable(findInAvailable(required_cell), std::move(new_filler));
    }
    
    void releaseCell(CellCPtr cell);
  
  public:
    void lock()    ;
    void unlock()  ;
    bool try_lock();
  
  private:
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
    // Из этого списка раздаются указатели на клетки
    // для учёта их другими сущностями.
    // Изменять их может только внутренняя реализация
    // бассейна клеток - через const_cast<CellPtr>.
    std::list<CellCPtr> available_cells;
    
    TextureStorage background_texture;
    sf::Sprite background;
    
    sf::RenderWindow& window;
    
    std::mutex cells_mutex;
};




#endif //SNAKE_CELLSPOOL_HPP
