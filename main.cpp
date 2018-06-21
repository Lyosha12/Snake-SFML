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
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
using namespace std::chrono_literals;

#include <SFML/Graphics.hpp>

#include "Coord/Coord.hpp"
#include "ErrorPrinter/ErrorPrinter.hpp"
#include "DefaultRectangle/DefaultRectangle.hpp"
#include "Cell/Cell.hpp"
#include "TimeCounter/TimeCounter.hpp"
#include "TextureStorage/TextureStorage.hpp"

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
    CellsPool(
        size_t count_cells_x,
        size_t count_cells_y,
        sf::RenderWindow& window,
        DefaultRectangle const& settings
    )
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
    
    struct RequestedCell {
        Cell* cell;
        std::unique_ptr<Cell::Filler> prev_filler;
        void operator() (Snake& snake) const {
            if(prev_filler)
                prev_filler->modify(snake);
        }
    };
    template <class Filler>
    RequestedCell getRandCell() {
        size_t i = 0;
        size_t rand_cell = std::rand()%available_cells.size();
        auto runner = available_cells.begin(); // Пробежимся по всем свободным клеткам.
        while(i++ != rand_cell) // Пока не найдём выбранную случайную клетку.
            ++runner;
    
        // Удалим клетку из свободных,
        // если новый её заполнитель недоступен для использования.
        // Вернём клетку и её предыдущий заполнитель.
        std::unique_ptr<Cell::Filler> new_filler(new Filler(default_rectangle, **runner));
        return kickFromAvailable(runner, std::move(new_filler));
    }
    template <class Filler>
    RequestedCell getNearCell(Cell* target) {
        // Берём случайную клетку в радиусе одной от заданной.
        
        // Найдём её соседей
        Cell* up    = extractCell(target->coord + Coord{ 0, -1});
        Cell* down  = extractCell(target->coord + Coord{ 0,  1});
        Cell* right = extractCell(target->coord + Coord{ 1,  0});
        Cell* left  = extractCell(target->coord + Coord{-1,  0});
        std::vector<Cell*> neighbors = {up, down, right, left};
        
        // Выберем случайную клетку, доступную к использованию.
        while(!neighbors.empty()) {
            size_t rand_neighbor = std::rand()%neighbors.size();
            Cell* neighbor = neighbors[rand_neighbor];
    
            if(neighbor->is_usable) {
                std::unique_ptr<Cell::Filler> new_filler(new Filler(default_rectangle, *neighbor));
                return kickFromAvailable(findInAvailable(neighbor), std::move(new_filler));
            } else
                neighbors.erase(neighbors.begin() + rand_neighbor);
        }
        
        throw NotFoundFreeCell(*target);
    }
    template <class Filler>
    RequestedCell getNearCell(Cell* target, Coord direction) {
        // Возьмём клетку по заданному направлению от текущей.
        Cell* required_cell = extractCell(target->coord + direction);
        std::unique_ptr<Cell::Filler> new_filler(new Filler(default_rectangle, *required_cell));
        return kickFromAvailable(findInAvailable(required_cell), std::move(new_filler));
    }
    
    void releaseCell(Cell* cell) {
        cell->filler = nullptr;
        // Если клетка бонусная, то она уже была в списке доступных
        // И её не нужно добавлять заново.
        if(!cell->is_usable)
            available_cells.push_front(cell);
    }
    
    
  private:
    RequestedCell kickFromAvailable(
        std::list<Cell*>::iterator runner,
        std::unique_ptr<Cell::Filler> new_filler
    ) {
        Cell* cell = *runner;
        // Если клетка бонусная, то из доступных её удалять не нужно.
        if(!cell->is_usable)
            available_cells.erase(runner);
        
        std::unique_ptr<Cell::Filler> prev_filler(std::move(cell->filler));
        cell->filler = std::move(new_filler);
        return { cell, std::move(prev_filler) };
    }
    Coord normalize(Coord coord) const {
        // Обеспечивает перепрыгивание через границу
        // поля на противоположную часть.
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
    std::list<Cell*>::iterator findInAvailable(Cell* cell) {
        auto runner = available_cells.begin();
        while(runner != available_cells.end() && *runner != cell)
            ++runner;
        
        if(runner != available_cells.end())
            return runner;
        else
            throw NotFoundFreeCell(*cell);
    }
    
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(background);
        for(auto const& row: cells)
            for(auto const& cell: row)
                target.draw(cell, states);
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
  private:
    class SnakeFiller: public Cell::Filler {
      public:
        SnakeFiller(
            DefaultRectangle const& default_rectangle,
            Cell& cell,
            sf::Texture const& texture
        )
        : Filler(createSprite(default_rectangle, cell.coord, texture))
        { cell.is_usable = false; }
        
        
        sf::Sprite createSprite(
            DefaultRectangle const& default_rectangle,
            Coord const& coord,
            sf::Texture const& texture
        ) const {
            sf::Sprite sprite = default_rectangle.configure(
                DefaultRectangle::Configurator(coord, texture)
            );
            
            sf::Vector2f scale = {
                default_rectangle.getSize().x / texture.getSize().x,
                default_rectangle.getSize().y / texture.getSize().y
            };
            
            sprite.setScale(scale);
            
            return sprite;
        }
    };
    class SnakeHead: public SnakeFiller {
      public:
        SnakeHead(DefaultRectangle const& default_rectangle, Cell& cell)
        : SnakeFiller(default_rectangle, cell, texture)
        {  }
      
      private:
        inline static TextureStorage texture = std::string("Head.png");
    };
    class SnakeBody: public SnakeFiller {
      public:
        SnakeBody(DefaultRectangle const& default_rectangle, Cell& cell)
        : SnakeFiller(default_rectangle, cell, texture)
        {  }
      
      private:
        inline static TextureStorage texture = std::string("Body.png");
    };
    
  public:
    enum class Direction { Up, Down, Left, Right };
    
  public:
    Snake(CellsPool& cells_pool)
    : cells_pool(cells_pool)
    {
        addHead();
        addBody();
        findHeadDirection();
    }
    
    void move() {
        if(!move_time.isIntervalPassed())
           return;
        
        tryChangeDirection();
    
        // Получим новую голову по направлению движения относительно текущей головы.
        CellsPool::RequestedCell new_head = cells_pool.getNearCell<SnakeHead>(body.front(), direction);
        
        // Освободим клетку старой головы.
        cells_pool.releaseCell(body.front());
        // Удалим старую голову из списка.
        body.pop_front();
        
        // Добавим часть тела в список между новой головой и удалённой прошлой.
        // Т.к. бонус не мог появиться между удалением текущей головы и
        // добавлением части тела вместо неё,
        // будем игнорировать прошлый заполнитель клетки.
        body.push_front(cells_pool.getNearCell<SnakeBody>(new_head.cell, -direction).cell);
        // Добавим вслед за частью тела новую голову.
        body.push_front(new_head.cell);
        
        // Освободим клетку хвоста.
        cells_pool.releaseCell(body.back());
        body.pop_back();
        
        // Дадим возможность потенциальному бонусу на клетке, где теперь
        // нахдится голова змейки, изменить змейку.
        new_head(*this);
    }
    void changeDirection(Direction direction) {
        // Внешнее управление змейкой посредством пользовательского ввода.
        switch(direction) {
            case Direction::Up   : moves.push({ 0, -1}); break;
            case Direction::Down : moves.push({ 0,  1}); break;
            case Direction::Left : moves.push({-1,  0}); break;
            case Direction::Right: moves.push({ 1,  0}); break;
        }
    }
    
  private:
    void addHead() {
        // Разместим голову в случайном месте поля.
        // Потом, если попали на какую-то бонусную клетку,
        // применим бонус с неё.
        CellsPool::RequestedCell head = cells_pool.getRandCell<SnakeHead>();
        body.push_back(head.cell);
        head(*this);
    }
    void addBody() {
        // Создадим параметры змейки.
        size_t max_start_parts = 4;
        size_t guaranteed_parts = 2;
        size_t additional_parts = rand()%(max_start_parts - guaranteed_parts);
        size_t start_parts = additional_parts + guaranteed_parts;
        
        // Сгенерируем остальное тело.
        try {
            while(start_parts--) {
                // Полученная клетка может быть бонусной.
                CellsPool::RequestedCell body_part = cells_pool.getNearCell<SnakeBody>(body.back());
                
                body.push_back(body_part.cell);
                // Поэтому после присоединения её к телу дадим возможность бонусу изменить змейку.
                body_part(*this);
            }
        } catch(CellsPool::NotFoundFreeCell const& e) {
            // Заканчиваем построение змеи - нет клеток для продолжения.
        }
    }
    void findHeadDirection() {
        // Узнаем направление змейки. От координат головы
        // отнимем координаты блока перед головой.
        Cell* head = *body.begin();
        Cell* prev_head = *++body.begin();
        direction = head->coord - prev_head->coord;
    }
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
    TimeCounter<std::chrono::steady_clock> move_time = 180ms;
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
