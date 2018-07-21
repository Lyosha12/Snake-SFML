//
// Created by Lyosha12 on 22.06.2018.
//

#include "CellsPool.hpp"
#include "DefaultRectangle/DefaultRectangle.hpp"
#include "Cell/Fillers/FreeCellFiller.hpp"

CellsPool::CellsPool(
    size_t count_cells_x,
    size_t count_cells_y,
    sf::RenderWindow& window,
    DefaultRectangle const& settings
)
    : default_rectangle(settings)
    , count_cells_x(count_cells_x)
    , count_cells_y(count_cells_y)
    , background_texture({"Background.png", true})
    , background(background_texture)
    , window(window)
{
    // Установим спрайту размер для замощённой текстуры.
    background.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));
    
    // Т.к. unique_ptr копировать нельзя, то вот так вот получается.
    cells.resize(count_cells_y);
    for(auto& row: cells) {
        row = std::move(std::vector<Cell>(count_cells_x));
    }
    
    for(size_t y = 0; y != count_cells_y; ++y) {
        for(size_t x = 0; x != count_cells_x; ++x) {
            cells[y][x].coord = {x, y};
            cells[y][x].filler = fillerCreator<FreeCellFiller>(cells[y][x].coord);
            available_cells.push_back(&cells[y][x]);
        }
    }
}

void CellsPool::releaseCell(CellCPtr cell_to_release) {
    if(!cell_to_release) {
        return;
    }
    
    CellPtr returned_cell = const_cast<CellPtr>(cell_to_release);
    
    // Добавим вернувшуюся клетку в список доступных.
    available_cells.push_front(returned_cell);
    returned_cell->filler = fillerCreator<FreeCellFiller>(returned_cell->coord);
}


void CellsPool::lock()     const { cells_mutex.lock();            }
void CellsPool::unlock()   const { cells_mutex.unlock();          }
bool CellsPool::try_lock() const { return cells_mutex.try_lock(); }



CellsPool::RequestedCell CellsPool::replaceFiller(CellPtr target, FillerUPtr new_filler) {
    // Заменяем заполнитель переданным
    std::unique_ptr<Filler> prev_filler(std::move(target->filler));
    target->filler = std::move(new_filler);
    
    // и возвращаем клетку со старым заполнителем.
    return { target, std::move(prev_filler) };
}
CellsPool::RequestedCell CellsPool::kickFromAvailable(AvailablesIter target, FillerUPtr new_filler) {
    CellPtr ordered_cell = const_cast<CellPtr>(*target);
    // Удалим запрошенную клетку из доступных к использованию.
    available_cells.erase(target);
    
    // Сохраним прошлый заполнитель и поместим новый.
    return replaceFiller(ordered_cell, std::move(new_filler));
}


Coord CellsPool::normalize(Coord coord) const {
    // Обеспечивает перепрыгивание через границу
    // поля на противоположную часть.
    auto normalize_component = [] (int c, int max) {
        return c >= 0 ? c % max : max + c;
    };
    return Coord(
        normalize_component(coord.x, count_cells_x),
        normalize_component(coord.y, count_cells_y)
    );
}
CellsPool::CellPtr CellsPool::extractCell(Coord coord) {
    coord = normalize(coord);
    return &cells[coord.y][coord.x];
}
CellsPool::AvailablesIter CellsPool::findInAvailable(CellCPtr cell) {
    // При попытке получить клетку по направлению или соседнюю к заданной
    // она может быть недоступна. Если так, то данная функция
    // выбросит исключение NotFoundFreeCell.
    
    auto cur_cell = available_cells.begin();
    while(cur_cell != available_cells.end() && *cur_cell != cell)
        ++cur_cell;
    
    if(cur_cell != available_cells.end())
        return cur_cell;
    else
        throw NotFoundFreeCell(cell);
}

void CellsPool::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  //  std::lock_guard<std::mutex> lock(cells_mutex);
    target.draw(background, states);
    
    for(auto const& row: cells)
        for(auto const& cell: row)
            target.draw(cell, states);
}