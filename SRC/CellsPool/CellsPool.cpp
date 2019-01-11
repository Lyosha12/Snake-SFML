// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 22.06.2018.
//

#include "CellsPool.hpp"
#include "DefaultRectangle/DefaultRectangle.hpp"
#include "CellsPool/Cell/Fillers/FreeCell.hpp"

CellsPool::CellsPool(
    size_t count_cells_x,
    size_t count_cells_y,
    DefaultRectangle const& settings
)
    : default_rectangle(settings)
    , count_cells_x(count_cells_x)
    , count_cells_y(count_cells_y)
    , background_texture({"Background.png", true})
    , background(background_texture)
{
    // Установим спрайту размер для замощения текстурой.
    size_t window_width = size_t(count_cells_x * default_rectangle.getSize().x);
    size_t window_height = size_t(count_cells_y * default_rectangle.getSize().y);
    background.setTextureRect(sf::IntRect(0, 0, window_width,window_height));
    
    // Т.к. unique_ptr копировать нельзя, то вот так вот получается.
    cells.resize(count_cells_y);
    for(auto& row: cells) {
        row = std::move(std::vector<Cell>(count_cells_x));
    }
    
    // Инициализаруем все клетки поля их координатами и заполнителем.
    // Инициализируем список свободных клеток.
    for(size_t y = 0; y != count_cells_y; ++y) {
        for(size_t x = 0; x != count_cells_x; ++x) {
            cells[y][x].coord = {x, y};
            cells[y][x].filler = createFreeFiller(cells[y][x].coord);
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
    
    // И обновим её заполнитель.
    returned_cell->filler = createFreeFiller(returned_cell->coord);
}

CellsPool::RequestedCell CellsPool::getRandCell(FillerCreator filler_creator) {
    // Берём случайную клетку из свободных,
    // помещая в неё переданный заполнитель.
    
    if(available_cells.empty()) {
        throw NotFoundFreeCell({}, "rand free cell not exist");
    }
    
    size_t rand_cell = random() % available_cells.size();
    AvailablesIter requested_cell = getListElement(available_cells, rand_cell);
    
    FillerUPtr new_filler = filler_creator(default_rectangle, (*requested_cell)->coord);
    return kickFromAvailable(requested_cell, std::move(new_filler));
}
CellsPool::RequestedCell CellsPool::getNearCell(CellCPtr target, FillerCreator filler_creator) {
    // Берём случайную свободную клетку в радиусе одной от заданной.
    
    // Найдём её соседей
    CellCPtr up    = extractCell(target->coord + Coord{ 0, -1});
    CellCPtr down  = extractCell(target->coord + Coord{ 0,  1});
    CellCPtr right = extractCell(target->coord + Coord{ 1,  0});
    CellCPtr left  = extractCell(target->coord + Coord{-1,  0});
    std::vector<CellCPtr> neighbors = {up, down, right, left};
    
    // Выберем случайную клетку...
    while(!neighbors.empty()) {
        size_t rand_neighbor = random()%neighbors.size();
        CellCPtr neighbor = neighbors[rand_neighbor];
        
        // Если клетку возможно передать в управление другому, то передадим.
        if(neighbor->filler->isCanBeTake()) {
            FillerUPtr new_filler = filler_creator(default_rectangle, neighbor->coord);
            return kickFromAvailable(findInAvailable(neighbor), std::move(new_filler));
        } else
            neighbors.erase(neighbors.begin() + rand_neighbor);
    }
    
    // Сейчас это происходит только при создании змейки.
    throw NotFoundFreeCell(target, "near free cell not exist");
}
CellsPool::RequestedCell CellsPool::getCell(CellCPtr target, Coord direction, FillerCreator filler_creator) {
    return getCell(target->coord + direction, filler_creator);
}
CellsPool::RequestedCell CellsPool::getCell(Coord coord, FillerCreator filler_creator) {
    // Возьмём клетку по заданному направлению относительно текущей.
    CellPtr requested_cell = extractCell(coord);
    
    AvailablesIter available_cell = findInAvailable(requested_cell);
    // Создадим заполнитель.
    FillerUPtr new_filler = filler_creator(default_rectangle, requested_cell->coord);;
    if(available_cell != available_cells.end()) {
        // Заполнитель перемещается в запрошенную клетку
        // только если эта клетка занята только пустым заполнителем.
        return kickFromAvailable(available_cell, std::move(new_filler));
    } else {
        // * Если клетка занята, то проверим возможность забрать заполнитель клетки.
        // - Если можно забрать заполнитель, то заменим существующий заполнитель
        //   в запрошенной клетке только что созданным new_filler.
        //   Тогда змейка сможет применить бонус из полученного заполнителя
        // - Если же присутствующий заполнитель в клетке не допускает
        //   возможности его "взять", то возвращаем структуру RequestedCell
        //   без замены заполнителя в запрошенной клетке.
        //   Тогда змейка будет применять бонус из не взятого заполнителя
        //   без перемещения на запрошенную клетку.
        return requested_cell->filler->isCanBeTake()
               ? replaceFiller(requested_cell, std::move(new_filler))
               : RequestedCell{requested_cell, nullptr};
    }
}

void CellsPool::replaceFiller(CellCPtr target, FillerCreator filler_creator) {
    FillerUPtr&& new_filler = filler_creator(default_rectangle, target->coord);
    FillerUPtr& old_filler = const_cast<CellPtr>(target)->filler;
    
    std::swap(new_filler, old_filler);
}
CellsPool::RequestedCell CellsPool::replaceFiller(CellPtr target, FillerUPtr new_filler) {
    // Заменяем заполнитель переданным
    std::unique_ptr<Filler> prev_filler(std::move(target->filler));
    target->filler = std::move(new_filler);
    
    // и возвращаем клетку со старым заполнителем.
    return { target, std::move(prev_filler) };
}


void CellsPool::lock()     const { cells_mutex.lock();            }
void CellsPool::unlock()   const { cells_mutex.unlock();          }
bool CellsPool::try_lock() const { return cells_mutex.try_lock(); }


CellsPool::RequestedCell CellsPool::kickFromAvailable(AvailablesIter target, FillerUPtr new_filler) {
    CellPtr ordered_cell = const_cast<CellPtr>(*target);
    // Удалим запрошенную клетку из доступных к использованию.
    available_cells.erase(target); // Now 'target' is not valid.
    
    // Сохраним прошлый заполнитель и поместим новый.
    return replaceFiller(ordered_cell, std::move(new_filler));
}

Coord CellsPool::normalize(Coord coord) const {
    // Обеспечивает перепрыгивание через границу поля на противоположную часть.
    auto normalize_component = [] (int component, size_t max) {
        if(component >= 0) {
            return component % max;
        } else {
            // Тут можно было бы написать и max - 1.
            // Всё равно нет планов на то, что движение будет больше,
            // чем через один блок.
            return max + component;
        }
    };
    return Coord(
        normalize_component(coord.x, count_cells_x),
        normalize_component(coord.y, count_cells_y)
    );
}
CellsPool::CellPtr CellsPool::extractCell(Coord coord) {
    coord = normalize(coord);
    return &cells[coord.y][coord.x]; //-V108
}
CellsPool::AvailablesIter CellsPool::findInAvailable(CellCPtr cell) {
    // При попытке получить клетку по направлению или соседнюю к заданной
    // она может быть недоступна. Если так, то данная функция
    // выбросит исключение NotFoundFreeCell.
    
    // В поисках нужной клетки пройдёмся по списку доступных...
    auto cur_cell = available_cells.begin();
    while(cur_cell != available_cells.end() && *cur_cell != cell)
        ++cur_cell;
    
    // Возвращаем итератор конца, если клетки нет.
    return cur_cell;
}

CellsPool::FillerUPtr CellsPool::createFreeFiller(Coord coord) const {
    return Filler::makeFillerCreator<FreeCell>(0)(default_rectangle, coord);
}

void CellsPool::draw(sf::RenderTarget& target, sf::RenderStates states) const { //-V813
    // WARN: Получим deadlock в WindowForTests
    std::lock_guard<std::mutex> lock(cells_mutex);
    
    target.draw(background, states);
    for(auto const& row: cells)
        for(auto const& cell: row)
            target.draw(cell, states);
}