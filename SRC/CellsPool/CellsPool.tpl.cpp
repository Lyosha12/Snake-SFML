//
// Created by Lyosha12 on 11.07.2018.
//


template <class IncomingFiller>
CellsPool::RequestedCell CellsPool::getRandCell() {
    // Берём случайную клетку из свободных,
    // помещая в неё переданный заполнитель.
    
    if(available_cells.empty()) {
        throw NotFoundFreeCell({}, "rand free cell not exist");
    }
    
    size_t rand_cell = std::rand()%available_cells.size();
    AvailablesIter requested_cell = getListElement(available_cells, rand_cell);
    
    std::unique_ptr<Filler> new_filler = fillerCreator<IncomingFiller>(
        (*requested_cell)->coord
    );
    return kickFromAvailable(requested_cell, std::move(new_filler));
}

template <class IncomingFiller>
CellsPool::RequestedCell CellsPool::getNearCell(CellCPtr target) {
    // Берём случайную свободную клетку в радиусе одной от заданной.
    
    // Найдём её соседей
    CellCPtr up    = extractCell(target->coord + Coord{ 0, -1});
    CellCPtr down  = extractCell(target->coord + Coord{ 0,  1});
    CellCPtr right = extractCell(target->coord + Coord{ 1,  0});
    CellCPtr left  = extractCell(target->coord + Coord{-1,  0});
    std::vector<CellCPtr> neighbors = {up, down, right, left};
    
    // Выберем случайную клетку...
    while(!neighbors.empty()) {
        size_t rand_neighbor = std::rand()%neighbors.size();
        CellCPtr neighbor = neighbors[rand_neighbor];
        
        // ... доступную к использованию.
        if(neighbor->filler->isCanBeTake()) {
            std::unique_ptr<Filler> new_filler = fillerCreator<IncomingFiller>(
                neighbor->coord
            );
            return kickFromAvailable(findInAvailable(neighbor), std::move(new_filler));
        } else
            neighbors.erase(neighbors.begin() + rand_neighbor);
    }
    
    // Сейчас это происходит только при создании змейки.
    throw NotFoundFreeCell(target, "near free cell not exist");
}

template <class IncomingFiller>
CellsPool::RequestedCell CellsPool::getCell(CellCPtr target, Coord direction) {
    // Возьмём клетку по заданному направлению относительно текущей.
    CellPtr requested_cell = extractCell(target->coord + direction);
    
    std::unique_ptr<Filler> new_filler = fillerCreator<IncomingFiller>(
        requested_cell->coord
    );
    
    try {
        AvailablesIter available_cell = findInAvailable(requested_cell);
        return kickFromAvailable(available_cell, std::move(new_filler));
    } catch(NotFoundFreeCell& e) {
        // * Здесь запрошенная клетка однозначно занята.
        // * Вернём заполнитель клетки, если она доступна для посещения.
        // * Иначе заполнитель остаётся,
        //   а змейка уже будет применять бонус этой клетки на себе,
        //   не занимая её.
        return requested_cell->filler->isCanBeTake()
               ? replaceFiller(requested_cell, std::move(new_filler))
               : RequestedCell { requested_cell, nullptr };
    }
}

template <class IncomingFiller>
void CellsPool::replaceFiller(CellCPtr target) {
    // Старый заполнитель вызывает также и деструктор бонуса.
    fillerCreator<IncomingFiller>(target->coord).swap(const_cast<CellPtr>(target)->filler);
}




template <class IncomingFiller>
std::unique_ptr<Filler> CellsPool::fillerCreator(Coord const& sprite_location) const {
    return std::unique_ptr<Filler>(new IncomingFiller(default_rectangle, sprite_location));
}