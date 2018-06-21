//
// Created by Lyosha12 on 18.06.2018.
//

#ifndef SNAKE_CELL_HPP
#define SNAKE_CELL_HPP

#include <algorithm>

#include <SFML/Graphics.hpp>

#include "../Coord/Coord.hpp"
// #include "../Snake/Snake.hpp"
class Snake;

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
      public:
        Filler(sf::Sprite sprite);
        virtual void modify(Snake&) const;
        
      private:
        sf::Sprite sprite;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
    
  public:
    Cell() = default;
    Cell(Cell&& cell);
    
    Coord coord = {-1, -1};
    std::unique_ptr<Filler> filler = nullptr;
    bool is_usable = true; // ���������� ������ ����� ������� � ����� ������.
    
  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif //SNAKE_CELL_HPP
