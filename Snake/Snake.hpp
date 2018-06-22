//
// Created by Lyosha12 on 22.06.2018.
//

#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP

#include <queue>
#include <vector>
#include <chrono>
using namespace std::chrono_literals;

#include "../CellsPool/Cell/Cell.hpp"
#include "../CellsPool/CellsPool.hpp"
#include "../TimeCounter/TimeCounter.hpp"

class Snake {
  private:
    class SnakeFiller: public Cell::Filler {
      public:
        SnakeFiller(
            DefaultRectangle const& default_rectangle,
            Cell& cell,
            sf::Texture const& texture
        );
        
        sf::Sprite createSprite(
            DefaultRectangle const& default_rectangle,
            Coord const& coord,
            sf::Texture const& texture
        ) const ;
    };
    class SnakeHead: public SnakeFiller {
      public:
        SnakeHead(DefaultRectangle const& default_rectangle, Cell& cell);
      
      private:
        inline static TextureStorage
            texture = TextureStorage::LoadTextureParams{"Head.png", false};
    };
    class SnakeBody: public SnakeFiller {
      public:
        SnakeBody(DefaultRectangle const& default_rectangle, Cell& cell);
      
      private:
        inline static TextureStorage
            texture = TextureStorage::LoadTextureParams{"Body.png", false};
    };
  
  public:
    enum class Direction { Up, Down, Left, Right };
  
  public:
    Snake(CellsPool& cells_pool);
    
    void move();
    void changeDirection(Direction direction);
  
  private:
    void addHead();
    void addBody();
    void findHeadDirection();
    void tryChangeDirection();
  
  private:
    std::list<Cell const*> body;
    Coord direction = {0, 0};
    TimeCounter<std::chrono::steady_clock> move_time = 150ms;
    std::queue<Coord> moves;
    
    CellsPool& cells_pool;
};


#endif //SNAKE_SNAKE_HPP
