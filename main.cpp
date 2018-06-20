#include <ctime>
#include <cmath>
#include <exception>
#include <string>
#include <list>
#include <queue>
#include <chrono>
#include <memory>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <functional>
#include <cstdlib>
#include <windows.h>
using namespace std::chrono_literals;

#include <SFML/Graphics.hpp>

#include "Coord/Coord.hpp"
#include "ErrorPrinter/ErrorPrinter.hpp"
#include "DefaultRectangle/DefaultRectangle.hpp"
#include "Cell/Cell.hpp"
#include "TimeCounter/TimeCounter.hpp"
#include "TextureStorage/TextureStorage.hpp"





class SnakeHead: public Cell::Filler {
  public:
    SnakeHead(DefaultRectangle const& default_rectangle, Cell& cell)
    : Filler(createSprite(default_rectangle, cell.coord))
    { cell.is_usable = false; }

    
    sf::Sprite createSprite(DefaultRectangle const& default_rectangle, Coord const& coord) const {
        sf::Sprite sprite = default_rectangle.configure(DefaultRectangle::Configurator(coord, texture));
    
        sf::Vector2f scale = {
            default_rectangle.getSize().x / texture->getSize().x,
            default_rectangle.getSize().y / texture->getSize().y
        };
    
        sprite.setScale(scale);
    
        return sprite;
    }
  
  private:
    inline static TextureStorage texture = std::string("Head.png");
};
class SnakeBody: public Cell::Filler {
  public:
    SnakeBody(DefaultRectangle const& default_rectangle, Cell& cell)
    : Filler(createSprite(default_rectangle, cell.coord))
    { cell.is_usable = false; }
    
    sf::Sprite createSprite(DefaultRectangle const& default_rectangle, Coord const& coord) const {
        sf::Sprite sprite = default_rectangle.configure(DefaultRectangle::Configurator(coord, texture));
    
        sf::Vector2f scale = {
            default_rectangle.getSize().x / texture->getSize().x,
            default_rectangle.getSize().y / texture->getSize().y
        };
    
        sprite.setScale(scale);
    
        return sprite;
    }
  
  private:
    inline static TextureStorage texture = std::string("Body.png");
};

class CellsPool: public sf::Drawable {
  public:
    struct NotFoundFreeCell: public std::exception {
        NotFoundFreeCell(Cell const& cell, Coord direction = {0, 0})
        : cell(cell)
        , direction(direction)
        { }
        
        char const* what() const noexcept override {
            return "Free cell not found";
        }
        
        Cell const& cell;
        Coord direction;
    };
    
  public:
    CellsPool(size_t count_cells_x, size_t count_cells_y,
              sf::RenderWindow& window, DefaultRectangle const& settings)
    : default_rectangle(settings)
    , count_cells_x(count_cells_x)
    , count_cells_y(count_cells_y)
    , background_texture("Background.png", true)
    , background(background_texture)
    , window(window)
     {
         background.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));
         
         cells.resize(count_cells_y);
         for(auto& row: cells)
             row = std::move(std::vector<Cell>(count_cells_x));
         
         for(size_t y = 0; y != count_cells_y; ++y)
            for(size_t x = 0; x != count_cells_x; ++x) {
                cells[y][x].coord = {x, y};
                available_cells.push_back(&cells[y][x]);
            }
    }
    
    template <class Filler>
    Cell* getRandCell() {
        size_t i = 0;
        size_t rand_cell = std::rand()%available_cells.size();
        auto runner = available_cells.begin(); // Пробежимся по всем свободным клеткам.
        while(i++ != rand_cell) // Пока не найдём выбранную случайную клетку.
            ++runner;
    
        // Удалим клетку из свободных, заполнив её переданным типом клетки.
        return kickFromAvailable(runner, new Filler(default_rectangle, **runner));
    }
    template <class Filler>
    Cell* getNearCell(Cell* cell) {
        // Берём случайную клетку в радиусе одной от заданной.
        
        // Найдём её соседей
        Cell* up    = extractCell(cell->coord + Coord{ 0, -1});
        Cell* down  = extractCell(cell->coord + Coord{ 0,  1});
        Cell* right = extractCell(cell->coord + Coord{ 1,  0});
        Cell* left  = extractCell(cell->coord + Coord{-1,  0});
        std::vector<Cell*> neighbors = {up, down, right, left};
        
        // Выберем случайную клетку, доступную к использованию.
        while(!neighbors.empty()) {
            size_t rand_neighbor = std::rand()%neighbors.size();
            Cell* neighbor = neighbors[rand_neighbor];
    
            if(neighbor->is_usable) {
                Filler* filler = new Filler(default_rectangle, *neighbor);
                return kickFromAvailable(findInAvailable(neighbor), filler);
            } else
                neighbors.erase(neighbors.begin() + rand_neighbor);
        }
        
        throw NotFoundFreeCell(*cell);
    }
    template <class Filler>
    Cell* getNearCell(Cell* cell, Coord move_vector) {
        // Возьмём клетку по заданному направлению от текущей.
        Cell* required_cell = extractCell(cell->coord + move_vector);
        Filler* filler = new Filler(default_rectangle, *required_cell);
        return kickFromAvailable(findInAvailable(required_cell), filler);
    }
    void  releaseCell(Cell* cell) {
        // Освободить клетку от текущего заполнителя,
        // добавить в список свободных.
        cell->filler = nullptr;
        available_cells.push_front(cell);
    }
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(background);
        for(auto const& row: cells)
            for(auto const& cell: row)
                target.draw(cell, states);
    }
    
  private:
    Coord normalize(Coord coord) const {
        auto normalize_component = [] (int c, int max) {
            return c >= 0 ? c % max : max + c;
        };
        return Coord(
            normalize_component(coord.x, count_cells_x),
            normalize_component(coord.y, count_cells_y)
        );
    }
    Cell* extractCell(Coord coord) {
        coord = normalize(coord);
        return &cells[coord.y][coord.x];
    }
    Cell* kickFromAvailable(std::list<Cell*>::iterator runner, Cell::Filler* filler) {
        // Выбросить клетку из свободных и
        // обновить её содержание новым заполнителем.
        Cell* cell = *runner;
        available_cells.erase(runner);
        cell->filler.reset(filler);
        return cell;
    }
    std::list<Cell*>::iterator findInAvailable(Cell* cell) {
        auto runner = available_cells.begin();
        while(runner != available_cells.end() && *runner != cell)
            ++runner;
        
        if(runner == available_cells.end())
            throw NotFoundFreeCell(*cell);
        else
            return runner;
    }
  
    
  private:
    DefaultRectangle const& default_rectangle;
    size_t count_cells_x;
    size_t count_cells_y;
    
    std::vector<std::vector<Cell>> cells;
    std::list<Cell*> available_cells;
    
    TextureStorage background_texture;
    sf::Sprite background;
    
    sf::RenderWindow& window;
};

class Snake {
  public:
    enum class Direction { Up, Down, Left, Right };
    
  public:
    Snake(CellsPool& cells_pool, size_t max_start_parts = 4)
    : cells_pool(cells_pool)
    {
        // Разместим голову в случайном месте поля.
        body.push_back(cells_pool.getRandCell<SnakeHead>());
    
        // Создадим параметры змейки.
        int guaranteed_parts = 2;
        int additional_parts = rand()%(max_start_parts - guaranteed_parts);
        int start_parts = additional_parts + guaranteed_parts;
        try {
            // Сгенерируем остальное тело.
            while(start_parts--)
                body.push_back(cells_pool.getNearCell<SnakeBody>(body.back()));
        } catch(CellsPool::NotFoundFreeCell const& e) {
            // Заканчиваем построение змеи - нет клеток для продолжения.
        }
        
        // Узнаем направление змейки. От координат головы
        // отнимем координаты следующего блока после неё.
        Cell* head = *body.begin();
        Cell* after_head = *++body.begin();
        direction = head->coord - after_head->coord;
    }
    
    void move() {
        if(!move_time.isIntervalPassed())
           return;
        
        tryChangeDirection();
    
        // Получим новую голову по направлению движения относительно текущей головы.
        Cell* new_head = cells_pool.getNearCell<SnakeHead>(body.front(), direction);
        
        // Освободим клетку старой головы.
        cells_pool.releaseCell(body.front());
        // Удалим старую голову из списка.
        body.pop_front();
        
        // Добавим часть тела в список между новой головой и удалённой прошлой.
        body.push_front(cells_pool.getNearCell<SnakeBody>(new_head, -direction));
        // Добавим вслед за частью тела новую голову.
        body.push_front(new_head);
        
        // Освободим клетку хвоста.
        cells_pool.releaseCell(body.back());
        body.pop_back();
    }
    void changeDirection(Direction direction) {
        switch(direction) {
            case Direction::Up   : moves.push({ 0, -1}); break;
            case Direction::Down : moves.push({ 0,  1}); break;
            case Direction::Left : moves.push({-1,  0}); break;
            case Direction::Right: moves.push({ 1,  0}); break;
        }
    }
    
  private:
    void tryChangeDirection() {
        while(!moves.empty() && (moves.front() + direction == 0 || moves.front() == direction))
            moves.pop();
    
        if(!moves.empty()) {
            direction = moves.front();
            moves.pop();
        }
    }
    
  private:
    std::list<Cell*> body;
    Coord direction = {0, 0};
    TimeCounter<std::chrono::steady_clock> move_time = 150ms;
    std::queue<Coord> moves;
    
    
    CellsPool& cells_pool;
};

class Game {
    // Главный класс. Управляет игровым циклом и отрисовкой.
    
  public:
    Game(unsigned long width, unsigned long height,
          size_t count_cells_x, size_t count_cells_y,
          std::string FieldName)
    : default_rectangle(width/count_cells_x, height/count_cells_y)
    , window({width/count_cells_x*count_cells_x, height/count_cells_y*count_cells_y}, FieldName)
    , cells_pool(count_cells_x, count_cells_y, window, default_rectangle)
    , snake(cells_pool)
    { }
    
    void mainLoop() {
        try {
            while(window.isOpen()) {
                window.draw(cells_pool); // Отрисовываем все клетки поля.
                window.display();
                handle_events();
                snake.move(); // Двигаем змейку в соответствии с её направлением.
            }
        } catch(CellsPool::NotFoundFreeCell const& e) {
            // TODO: Реализовать показ завершения игры.
        } catch(std::exception const& e) {
            ErrorPrinter(e.what()).print();
        }
    }
    void handle_events() {
        sf::Event event;
        while(window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
                    return;
                    
                case sf::Event::KeyPressed:
                    // Изменим направление змейки
                    // в соответствии с нажатой клавишей.
                    switch(event.key.code) {
                        case sf::Keyboard::Up    :
                            snake.changeDirection(Snake::Direction::Up);
                            return;
                        case sf::Keyboard::Down  :
                            snake.changeDirection(Snake::Direction::Down);
                            return;
                        case sf::Keyboard::Left  :
                            snake.changeDirection(Snake::Direction::Left);
                            return;
                        case sf::Keyboard::Right :
                            snake.changeDirection(Snake::Direction::Right);
                            return;
                        default:
                            return;
                    }
                    
                default: ;
            }
        }
    }
    
  private:
    DefaultRectangle default_rectangle;
    sf::RenderWindow window;
    CellsPool cells_pool;
    Snake snake;
};

int main() {
    // Настройка "окружения".
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    srand(static_cast<unsigned int>(time(0)));
    
    Game(800, 600, 20, 20, "Snake").mainLoop();
    return 0;
}
