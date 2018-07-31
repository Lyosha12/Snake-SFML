//
// Created by Lyosha12 on 16.07.2018.

template <class InputFiller>
void Snake::replaceChapter(size_t chapter_index) {
    // Замена заполнителя - работа бассейна клеток. Переадресуем.
    cells_pool.replaceFiller<InputFiller>(*getListElement(body, chapter_index));
}


template <class IntervalType>
void Snake::setMoveInterval(IntervalType move_interval) {
    this->move_interval.setInterval<IntervalType>(move_interval);
}