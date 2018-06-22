//
// Created by Lyosha12 on 22.06.2018.
//

#ifndef SNAKE_REQUESTEDCELL_HPP
#define SNAKE_REQUESTEDCELL_HPP

#include "../Cell/Cell.hpp"

class Snake;

class RequestedCell {
    // * Бассейн клеток отдаёт этот объект всякий раз,
    //   как кто-то успешно завладеет клеткой.
    // * Обращаться напрямую к предыдущему заполнителю
    //   опасно: можно обратиться к nullptr -
    //   поэтому он помещён в private-часть.
    // * Возвращаемая клетка, напротив, должна быть доступна без проблем,
    //   чтобы вызывающий мог оставить её адрес
    //   у себя для последующего возврата в бассейн.
    
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
