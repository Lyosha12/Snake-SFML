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

#include "ErrorPrinter/ErrorPrinter.hpp"
#include "TimeCounter/TimeCounter.hpp"
#include "CellsPool/CellsPool.hpp"
#include "Snake/Snake.hpp"
#include "BonusManager/BonusManager.hpp"
class Game {
    // Главный класс. Управляет игровым циклом и отрисовкой.
    
  public:
    Game(unsigned long width, unsigned long height,
          size_t count_cells_x, size_t count_cells_y,
          std::string FieldName)
    : default_rectangle(width/count_cells_x, height/count_cells_y)
    , window(
        {
            static_cast<unsigned>(default_rectangle.getSize().x*count_cells_x),
            static_cast<unsigned>(default_rectangle.getSize().y*count_cells_y)
        },
        FieldName
      )
    , cells_pool(count_cells_x, count_cells_y, window, default_rectangle)
    , bonus_manager(cells_pool)
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
    BonusManager bonus_manager;
    CellsPool cells_pool;
    Snake snake;
};

int main() {
    // Настройка "окружения".
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    // srand(static_cast<unsigned int>(time(0)));
    
    Game(800, 600, 20, 20, "Snake").mainLoop();
    
    return 0;
}
