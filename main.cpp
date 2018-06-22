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
#include "TimeCounter/TimeCounter.hpp"
#include "CellsPool/CellsPool.hpp"
#include "CellsPool/DefaultRectangle/DefaultRectangle.hpp"

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
        std::lock_guard<CellsPool> lock(cells_pool);
        addHead();
        addBody();
        findHeadDirection();
    }
    
    void move() {
        if(!move_time.isIntervalPassed())
           return;
        
        tryChangeDirection();
    
        // Получим новую голову по направлению движения относительно текущей головы.
        RequestedCell new_head = cells_pool.getNearCell<SnakeHead>(body.front(), direction);
        
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
        new_head.modify(*this);
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
        RequestedCell head = cells_pool.getRandCell<SnakeHead>();
        body.push_back(head.cell);
        head.modify(*this);
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
                RequestedCell body_part = cells_pool.getNearCell<SnakeBody>(body.back());
                
                body.push_back(body_part.cell);
                // Поэтому после присоединения её к телу дадим возможность бонусу изменить змейку.
                body_part.modify(*this);
            }
        } catch(NotFoundFreeCell const& e) {
            // Заканчиваем построение змеи - нет клеток для продолжения.
        }
    }
    void findHeadDirection() {
        // Узнаем направление змейки. От координат головы
        // отнимем координаты блока перед головой.
        Cell const* head = *body.begin();
        Cell const* prev_head = *++body.begin();
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
    std::list<Cell const*> body;
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
        } catch(NotFoundFreeCell const& e) {
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
