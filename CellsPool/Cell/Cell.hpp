//
// Created by Lyosha12 on 18.06.2018.
//

#ifndef SNAKE_CELL_HPP
#define SNAKE_CELL_HPP

#include <SFML/Graphics.hpp>

#include "../../Coord/Coord.hpp"
// #include "../RequestedCell/RequestedCell.hpp"

// #include "../Snake/Snake.hpp"
class Snake;
class RequestedCell;

class Cell: public sf::Drawable {
    // ������������ ������ �� ����.
    // ������ ����� ����������, �����������
    // ���� ��������������(usable) ��� ���.
    // ����� ����������� - ��, ��� ��� ��������.
    // ����������� ������������ ������� ������ (cells_pool).
    
  public:
    class Filler: public sf::Drawable {
      // ����������� ������ - ��� ����� ������.
      // ��� �������� � ����� ���������� ��������� ����� ������.
    
      // ������ ������ ������ ����� ������.
      // �, � ����������� �� ���������� ������� modify,
      // ������ ����� �������� ��� ��� �����.
      
      // ��� ��� ����������� ����� ���� ����, �� �������� modify ������.
      // ��� ������������ ��������������� ����� RequestedCell.
        friend RequestedCell;
        
      public:
        Filler(sf::Sprite sprite);
        virtual ~Filler() = default;
        
      private:
        virtual void modify(Snake&) const;
        sf::Sprite sprite;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
  
  public:
    using FillerUPtr = std::unique_ptr<Filler>;
    using CellCPtr   = Cell const*;
    using CellPtr    = Cell*;
    
  public:
    Cell() = default;
    Cell(Cell&& cell);
    
    Coord coord = {-1, -1};
    // ����������� ��� ������ ��-��������� �����������.
    // �������� ���� � ���� ������ �� ��������. �������
    // �������� ���� �������������� �� ���������� �������
    // ��������� ������������� ���������.
    std::unique_ptr<Filler> filler = nullptr;
    bool is_usable = true; // ���������� ������ ����� ������� � ����� ������.
    
  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif //SNAKE_CELL_HPP
