// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <exception>
#include <string>
#include <windows.h>

#include <SFML/Graphics.hpp>

#include "Utility/FatalError/FatalError.hpp"
#include "CellsPool/DefaultRectangle/DefaultRectangle.hpp"
#include "CellsPool/CellsPool.hpp"
#include "Snake/Snake.hpp"
#include "Snake/EndGame.hpp"
#include "BonusManager/BonusManager.hpp"
#include "Utility/ThreadGuard/ThreadGuard.hpp"
#include "AudioPlayer/AudioController.hpp"
#include "Icon/IconOpenGL.h"

class Game {
    // Главный класс. Управляет игровым циклом и отрисовкой.
    
  public:
    Game(
        unsigned width, unsigned height,
        size_t count_cells_x, size_t count_cells_y
    )
    : default_rectangle({width/count_cells_x, height/count_cells_y})
    , window(
        {
            static_cast<unsigned>(default_rectangle.getSize().x*count_cells_x),
            static_cast<unsigned>(default_rectangle.getSize().y*count_cells_y)
        },
        "Snake"
      )
    , cells_pool(count_cells_x, count_cells_y, default_rectangle)
    , snake(cells_pool)
    , bonus_manager(cells_pool)
    {
        window.setFramerateLimit(60);
        window.setIcon(SNAKE_ICON.width, SNAKE_ICON.height, SNAKE_ICON.pixel_data);
    }
    
    void gameLoop() {
        try {
            while(window.isOpen()) {
                window.draw(cells_pool); // Отрисовываем все клетки поля.
                window.display();
                handleEvents();
                snake.update(); // Двигаем змейку в соответствии с её направлением.
            }
            
        }
        catch(EndGame const&) {
            // TODO: нарисовать "you lose".
            // return;
        }
        
        catch(std::exception const& e) {
            FatalError(e.what()).print();
        }
    }
    void handleEvents() {
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
    BonusManager bonus_manager;
    AudioController audio_player;
};

int main() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    
    Game(800, 800, 20, 20).gameLoop();
    
    return 0;
}
