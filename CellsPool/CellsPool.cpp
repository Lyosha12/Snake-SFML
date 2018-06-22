//
// Created by Lyosha12 on 22.06.2018.
//

#include "CellsPool.hpp"

CellsPool::CellsPool(
    size_t count_cells_x,
    size_t count_cells_y,
    sf::RenderWindow& window,
    DefaultRectangle const& settings
)
    : default_rectangle(settings)
    , count_cells_x(count_cells_x)
    , count_cells_y(count_cells_y)
    , background_texture("Background.png", true)
    , background(background_texture)
    , window(window)
{
    
    background.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));
    
    cells.resize(count_cells_y);
    for(auto& row: cells) {
        row = std::move(std::vector<Cell>(count_cells_x));
    }
    
    for(size_t y = 0; y != count_cells_y; ++y) {
        for(size_t x = 0; x != count_cells_x; ++x) {
            cells[y][x].coord = {x, y};
            available_cells.push_back(&cells[y][x]);
        }
    }
}

void CellsPool::releaseCell(CellCPtr cell) {
    CellPtr returned_cell = const_cast<CellPtr>(cell);
    
    returned_cell->filler = nullptr;
    // ���� ������ ��������, �� ��� ��� ���� � ������ ���������
    // � � �� ����� ��������� ������.
    if(!returned_cell->is_usable)
        available_cells.push_front(returned_cell);
}

void CellsPool::lock()     { cells_mutex.lock();            }
void CellsPool::unlock()   { cells_mutex.unlock();          }
bool CellsPool::try_lock() { return cells_mutex.try_lock(); }

RequestedCell CellsPool::kickFromAvailable(AviablesIter runner, FillerUPtr new_filler) {
    CellPtr cell = const_cast<CellPtr>(*runner);
    // ���� ������ ��������, �� �� ��������� � ������� �� �����.
    if(!cell->is_usable)
        available_cells.erase(runner);
    
    std::unique_ptr<Cell::Filler> prev_filler(std::move(cell->filler));
    cell->filler = std::move(new_filler);
    return { cell, std::move(prev_filler) };
}
Coord CellsPool::normalize(Coord coord) const {
    // ������������ �������������� ����� �������
    // ���� �� ��������������� �����.
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
CellsPool::AviablesIter CellsPool::findInAvailable(CellCPtr cell) {
    // ��� ������� �������� ������ �� ����������� ��� �������� � ��������
    // ��� ����� ���� ����������. ���� ���, �� ������ �������
    // �������� ���������� NotFoundFreeCell.
    
    auto runner = available_cells.begin();
    while(runner != available_cells.end() && *runner != cell)
        ++runner;
    
    if(runner != available_cells.end())
        return runner;
    else
        throw NotFoundFreeCell(*cell);
}

void CellsPool::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background);
    for(auto const& row: cells)
        for(auto const& cell: row)
            target.draw(cell, states);
}