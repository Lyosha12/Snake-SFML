//
// Created by Lyosha12 on 22.06.2018.
//

#ifndef SNAKE_REQUESTEDCELL_HPP
#define SNAKE_REQUESTEDCELL_HPP

#include "../Cell/Cell.hpp"

class Snake;

class RequestedCell {
    // * ������� ������ ����� ���� ������ ������ ���,
    //   ��� ���-�� ������� ��������� �������.
    // * ���������� �������� � ����������� �����������
    //   ������: ����� ���������� � nullptr -
    //   ������� �� ������� � private-�����.
    // * ������������ ������, ��������, ������ ���� �������� ��� �������,
    //   ����� ���������� ��� �������� � �����
    //   � ���� ��� ������������ �������� � �������.
    
    using FillerUPtr = Cell::FillerUPtr;
    using CellCPtr   = Cell::CellCPtr;
  private:
    FillerUPtr prev_filler;
  
  public:
    CellCPtr cell;
  
  public:
    RequestedCell(CellCPtr cell, FillerUPtr prev_filler);
    void modify (Snake& snake) const;
};

#endif //SNAKE_REQUESTEDCELL_HPP
