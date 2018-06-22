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
    // ����� �������� �� ������������� ������ �����
    // ��������� �� ����. ����� �������,
    // �������� � ������� ���������� ���� ��������.
    
    // ��� ����������� ������. ������, ��� ���������� � ����,
    // ������� ����� ��������� ��� �������.
    
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
        while(i++ != rand_cell) // ���� �� ����� ��������� ��������� ������.
            ++cells_runner;
        
        // ������ ������ �� ���������,
        // ���� ����� � ����������� ���������� ��� �������������.
        // ����� ������ � � ���������� �����������.
        std::unique_ptr<Cell::Filler> new_filler(
            // TODO: ������ Filler ������ �������� ����������� ������ � ���� � ������������?
            new Filler(default_rectangle, const_cast<Cell&>(**cells_runner))
        );
        return kickFromAvailable(cells_runner, std::move(new_filler));
    }
    template <class Filler>
    RequestedCell getNearCell(CellCPtr target) {
        // ���� ��������� ������ � ������� ����� �� ��������.
        
        // ����� � �������
        CellCPtr up    = extractCell(target->coord + Coord{ 0, -1});
        CellCPtr down  = extractCell(target->coord + Coord{ 0,  1});
        CellCPtr right = extractCell(target->coord + Coord{ 1,  0});
        CellCPtr left  = extractCell(target->coord + Coord{-1,  0});
        std::vector<CellCPtr> neighbors = {up, down, right, left};
        
        // ������� ��������� ������, ��������� � �������������.
        while(!neighbors.empty()) {
            size_t rand_neighbor = std::rand()%neighbors.size();
            CellCPtr neighbor = neighbors[rand_neighbor];
            
            if(neighbor->is_usable) {
                // TODO: ������ Filler ������ �������� ����������� ������ � ���� � ������������?
                FillerUPtr new_filler(new Filler(default_rectangle, const_cast<Cell&>(*neighbor)));
                return kickFromAvailable(findInAvailable(neighbor), std::move(new_filler));
        } else
                neighbors.erase(neighbors.begin() + rand_neighbor);
        }
        
        throw NotFoundFreeCell(*target, "near");
    }
    template <class Filler>
    RequestedCell getNearCell(CellCPtr target, Coord direction) {
        // ������ ������ �� ��������� ����������� �� �������.
        CellPtr required_cell = extractCell(target->coord + direction);
        
        // TODO: ������ Filler ������ �������� ����������� ������ � ���� � ������������?
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
    // ������� ��� ������ ��������� � �������� � ����.
    DefaultRectangle const& default_rectangle;
    size_t count_cells_x;
    size_t count_cells_y;
    
    std::vector<std::vector<Cell>> cells;
    // �� ����� ������ ��������� ��������� �� ������
    // ��� ����� �� ������� ����������.
    // �������� �� ����� ������ ���������� ����������
    // �������� ������ - ����� const_cast<CellPtr>.
    std::list<CellCPtr> available_cells;
    
    TextureStorage background_texture;
    sf::Sprite background;
    
    sf::RenderWindow& window;
    
    std::mutex cells_mutex;
};




#endif //SNAKE_CELLSPOOL_HPP
