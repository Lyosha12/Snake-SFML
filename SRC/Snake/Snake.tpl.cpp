//
// Created by Lyosha12 on 16.07.2018.
//


template <class FillerType>
void Snake::pushChapter(size_t chapter_index) {
    // Возьмём итератор элемента, перед которым будем вставлять.
    auto where_insert = getListElement(body, chapter_index);
    
    // * Вычислим направление, по которому возьмём клетку.
    // * Расположение клетки относительно where_insert различно.
    //   Поэтому вычисляем направление взятия клетки как:
    // - разницу текущей и предыдущей клетки, если where_insert - голова/тело.
    // - разницу предыдущей клетки и текущей, если where_insert - хвост.
    Coord direction = where_insert == --body.end()
                      ? (*(where_insert - 1))->coord - (*where_insert      )->coord
                      : (*where_insert      )->coord - (*(where_insert + 1))->coord;
    
    CellsPool::RequestedCell r = cells_pool.getCell<FillerType>(
        *where_insert, direction
    );
    
    // Вставка после головы или хвоста очевидны.
    // Вставим в середину только при наличии свободной клетки по месту вставки,
    // иначе придётся ещё гадать куда вставлять, что двигать и как решить
    // ситуацию, когда попытаемся расшириться, а места уже нет.
    // Поэтому расширение происходит только при движении - поедании еды.
    
    // Получив нужную клетку по нужному направлению, вставим в нужное место.
    if(r.prev_filler != nullptr)
        body.insert(where_insert, r.cell);
    else {
        // Иначе применим отрицательный бонус на змейку, не изменяющий
        // её положения на поле в данный момент.
        active_effects.push_back(std::move(r.cell->filler->getBonus(*this)));
    }
}



template <class InputFiller>
void Snake::replaceChapter(size_t chapter_index) {
    // Замена заполнителя - работа бассейна клеток. Переадресуем.
    cells_pool.replaceFiller<InputFiller>(*getListElement(body, chapter_index));
}


template <class IntervalType>
void Snake::setMoveInterval(IntervalType move_interval) {
    this->move_interval.setInterval(move_interval);
}