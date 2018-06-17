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
#include <windows.h>
using namespace std;
#include <SFML/Graphics.hpp>

namespace MyColors {
  sf::Color const gray         = sf::Color(128, 128, 128);
  sf::Color const royal_blue   = sf::Color(65 , 105, 225);
  sf::Color const tomato       = sf::Color(255, 99 , 71 );
  sf::Color const orange       = sf::Color(255, 165,  0 );
  sf::Color const gold         = sf::Color(255, 215,  0 );
  sf::Color const lime_green   = sf::Color(50 , 205, 50 );
  sf::Color const dark_green   = sf::Color(0  , 100,  0 );
}

struct Coord {
    // Описывает координату квадрата в матрице квадратов.
    // От левого верхнего угла: x - по ширине, y - по высоте.
    // Координаты целые знаковые - это позволяет использовать
    // их как компоненты вектора направления чего-либо (змейки).
    int x = -1, y = -1;
    double vectorLenght() const {
        return sqrt(x*x + y*y);
    }
    
    bool  operator== (double value) const {
        return abs(vectorLenght() - value) < 1e-5;
    }
    bool  operator== (Coord const& rhs) {
        return this->x == rhs.x && this->y == rhs.y;
    }
    bool  operator!= (int value) const {
        return !(*this == value);
    }
    Coord operator+  (Coord const& rhs) const {
        return {this->x + rhs.x, this->y + rhs.y};
    }
    Coord operator-  (Coord const& rhs) const {
        return *this + -rhs;
    }
    Coord operator-  () const {
        return {-this->x, -this->y};
    }
};
class Cell: public sf::Drawable {
  public:
    class Filler: public sf::Drawable {
      public:
        enum class Type {
            Barrier  ,
            Eat      ,
            Poison   ,
            Destroyer
        };
      
      public:
        Filler(sf::Shape* shape): shape(shape) { }
        
        void move(float x, float y) {
            shape->move(x, y);
        }
        virtual Type getType() const = 0;
        
      private:
        unique_ptr<sf::Shape> shape;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override  {
            target.draw(*shape, states);
        }
    };
    
  public:
    Cell() = default;
    Cell(Cell&& cell)
    : coord(cell.coord)
    , filler(move(cell.filler))
    , isUsable(cell.isUsable)
    , isPrintable(cell.isPrintable)
    {}
    
    Coord coord = {-1, -1};
    unique_ptr<Filler> filler = nullptr;
    bool isUsable = true;
    bool isPrintable = false;
    
  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override  {
        target.draw(*filler, states);
    }
};

struct RectangleSettings {
    RectangleSettings(float cell_width, float cell_height)
    : default_rectangle({cell_width, cell_height})
    {
        default_rectangle.setFillColor(MyColors::royal_blue);
    }
    sf::RectangleShape default_rectangle;
    
    struct Settings {
        Settings(Coord pos_on_field, sf::Color color, float scale = 1)
        : pos_on_field(pos_on_field)
        , color(color)
        , scale(scale)
        { }
    
        sf::RectangleShape configure(sf::RectangleShape rect) {
            setPos(rect);
            rect.setFillColor(color);
            setScale(rect);
            
            return rect;
        }
  
      private:
        void setPos(sf::RectangleShape& rect) {
            float width  = rect.getSize().x;
            float height = rect.getSize().y;
            rect.setPosition(width * pos_on_field.x, height * pos_on_field.y);
        }
        void setScale(sf::RectangleShape& rect) {
            if(abs(scale - 1) < 1e-5)
                return;
            
            float inverse = 1 - scale;
            rect.move(rect.getSize().x * inverse/2, rect.getSize().y * inverse/2);
            rect.setScale({scale, scale});
        }
        
      private:
        Coord pos_on_field;
        sf::Color color;
        float scale;
    };
    
    sf::RectangleShape rectangleGenerator(Settings settings) const {
        return settings.configure(default_rectangle);
    }
};
class Barrier  : public Cell::Filler {
  public:
    Type getType() const override { return Type::Barrier; }
    Barrier(RectangleSettings const& settings, Cell& cell)
    : Filler(new sf::RectangleShape(settings.rectangleGenerator(
            { cell.coord, MyColors::gray }
    )))
    {
        cell.isUsable = false;
        cell.isPrintable = true;
    } // gray
};
class SnakePart: public Cell::Filler {
  public:
    Type getType() const override { return Type::Barrier; }
    SnakePart(Cell& cell, sf::RectangleShape const& rect)
    : Filler(new sf::RectangleShape(rect))
    {
        cell.isUsable = false;
        cell.isPrintable = true;
    }
};
class Bonus    : public Cell::Filler {
  public:
    Bonus(Cell& cell, sf::RectangleShape const& rect)
    : Filler(new sf::RectangleShape(rect))
    {
        cell.isUsable = true;
        cell.isPrintable = true;
    }
};
class SnakeHead: public SnakePart {
  public:
    SnakeHead(RectangleSettings const& settings, Cell& cell)
    : SnakePart(cell, settings.rectangleGenerator({cell.coord, MyColors::dark_green}))
    { }
};
class SnakeBody: public SnakePart {
  public:
    SnakeBody(RectangleSettings const& settings, Cell& cell)
    : SnakePart(cell, settings.rectangleGenerator({cell.coord, MyColors::lime_green}))
    { } // lime_green
};
class Eat      : public Bonus {
  public:
    Type getType() const override { return Type::Eat; }
    Eat(RectangleSettings const& settings, Cell& cell)
    : Bonus(cell, settings.rectangleGenerator({cell.coord, MyColors::orange}))
    { } // orange
};
class Poison   : public Bonus {
  public:
    Type getType() const override { return Type::Poison; }
    Poison(RectangleSettings const& settings, Cell& cell)
    : Bonus(cell, settings.rectangleGenerator({cell.coord, MyColors::tomato}))
    { } // tomato
};
class Destroyer: public Bonus {
  public:
    Type getType() const override { return Type::Destroyer; }
    Destroyer(RectangleSettings const& settings, Cell& cell)
    : Bonus(cell, settings.rectangleGenerator({cell.coord, MyColors::gold}))
    {  } // gold
};

class CellsPool {
  public:
    struct NotFoundFreeCell: public exception {
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
              sf::RenderWindow& window, RectangleSettings const& settings)
    : settings(settings)
    , count_cells_x(count_cells_x)
    , count_cells_y(count_cells_y)
    , window(window)
     {
         cells.resize(count_cells_y);
         for(auto& row: cells)
             row = move(vector<Cell>(count_cells_x));
         
         for(size_t y = 0; y != count_cells_y; ++y)
            for(size_t x = 0; x != count_cells_x; ++x) {
                cells[y][x].coord = {int(x), int(y)};
                available_cells.push_back(&cells[y][x]);
            }
    }
    
    float cell_width () { return settings.default_rectangle.getSize().x; }
    float cell_height() { return settings.default_rectangle.getSize().y; }
    
    Cell* extractCell(Coord coord) {
        int y = coord.y, x = coord.x;
        auto isInRange = [] (int z, int max) {
            return 0 <= z && z < max;
        };
    
        bool xInRange = isInRange(x, count_cells_x);
        bool yInRange = isInRange(y, count_cells_y);
    
        // Нормировка координат требуемой клетки.
        Cell* required_cell = nullptr;
        if(xInRange && yInRange) {
            required_cell = &cells[y][x];
        } else {
            if(yInRange) {
                if(x < 0)
                    required_cell = &cells[y][count_cells_x - 1];
                else // if(x >= int(count_cells_x))
                    required_cell = &cells[y][0];
            }
            
            else if(xInRange) {
                if(y < 0)
                    required_cell = &cells[count_cells_y - 1][x];
                else // if(y >= int(count_cells_y))
                    required_cell = &cells[0][x];
            }
            
            else
                throw logic_error("Both components outed of bounds");
        }
        
        return required_cell;
    }
    Cell* kickFromAvailable(list<Cell*>::iterator runner, Cell::Filler* filler, bool isPrintable = true) {
        // Выбросить клетку из свободных и
        // обновить её содержание новым заполнителем.
        Cell* cell = *runner;
        available_cells.erase(runner);
        cell->filler.reset(filler);
        cell->isPrintable = isPrintable;
        return cell;
    }
    list<Cell*>::iterator findInAvailable(Cell* cell) {
        auto runner = available_cells.begin();
        while(runner != available_cells.end() && *runner != cell)
            ++runner;
        
        if(runner == available_cells.end())
            throw NotFoundFreeCell(*cell);
        else
            return runner;
    }
    
    template <class Filler>
    Cell* getRandCell() {
        size_t i = 0;
        size_t rand_cell = rand()%available_cells.size();
        auto runner = available_cells.begin();
        while(i++ != rand_cell)
            ++runner;
    
        return kickFromAvailable(runner, new Filler(settings, **runner));
    }
    template <class Filler>
    Cell* getNearCell(Cell* cell) {
        size_t y = size_t(cell->coord.y), x = size_t(cell->coord.x);
        Cell* up    = y   != 0             ? &cells[y-1][x  ] : nullptr;
        Cell* down  = y+1 != count_cells_y ? &cells[y+1][x  ] : nullptr;
        Cell* right = x+1 != count_cells_x ? &cells[y  ][x+1] : nullptr;
        Cell* left  = x   != 0             ? &cells[y  ][x-1] : nullptr;
        vector<Cell*> neighbors = {up, down, right, left};
        
        while(!neighbors.empty()) {
            size_t rand_neighbor = rand() % neighbors.size();
            Cell* neighbor = neighbors[rand_neighbor];
            
            if(neighbor && neighbor->isUsable) {
                Filler* filler = new Filler(settings, *neighbor);
                return kickFromAvailable(findInAvailable(neighbor), filler);
            }
            else
                neighbors.erase(neighbors.begin() + rand_neighbor);
        }
        
        throw NotFoundFreeCell(*cell);
    }
    template <class Filler>
    Cell* getNearCell(Cell* cell, Coord move_vector, bool isPrintable = true) {
        Cell* required_cell = extractCell(cell->coord + move_vector);
        Filler* filler = new Filler(settings, *required_cell);
        return kickFromAvailable(findInAvailable(required_cell), filler, isPrintable);
    }
    void  releaseCell(Cell* cell) {
        cell->filler = nullptr;
        cell->isPrintable = false;
        available_cells.push_front(cell);
    }
    
    void display() {
        window.clear(settings.default_rectangle.getFillColor());
        
        for(auto& row: cells)
            for(auto& cell: row)
                if(cell.isPrintable)
                    window.draw(cell);
        
        window.display();
    }
    
  private:
    RectangleSettings const& settings;
    size_t count_cells_x;
    size_t count_cells_y;
    sf::RenderWindow& window;
    vector<vector<Cell>> cells;
    list<Cell*> available_cells;
};

class Snake {
  public:
    enum class Direction { Up, Down, Left, Right };
    
  public:
    Snake(CellsPool& cells_pool, size_t max_start_parts = 4,
          chrono::duration<int64_t, nano> move_time = 80ms)
    : move_time(move_time)
    , cells_pool(cells_pool)
    {
        body.push_back(cells_pool.getRandCell<SnakeHead>());
    
        int guaranteed_parts = 2;
        int additional_parts = rand()%(max_start_parts - guaranteed_parts);
        int start_parts = additional_parts + guaranteed_parts;
        try {
            while(start_parts--)
                body.push_back(cells_pool.getNearCell<SnakeBody>(body.back()));
        } catch(CellsPool::NotFoundFreeCell const& e) {
            // Заканчиваем построение змеи - нет клеток для продолжения.
        }
        
        direction = (*body.begin())->coord - (*++body.begin())->coord;
    }
    
    void move() {
        if(chrono::steady_clock::now() - last_move < move_time)
           return;
        last_move = chrono::steady_clock::now();
        tryChangeDirection();
    
        auto new_head = cells_pool.getNearCell<SnakeHead>(body.front(), direction, false);
        // slide(new_head->coord); // Создать видимость плавного перехода
        
        cells_pool.releaseCell(body.front());
        body.push_front(cells_pool.getNearCell<SnakeBody>(body.front(), {0, 0}));
        body.pop_front();
        
        body.push_front(new_head);
        body.front()->isPrintable = true;
        
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
    void slide(Coord destination) {
        float move_step = 4;
        size_t width  = size_t(cells_pool.cell_width()  * (1/move_step));
        size_t height = size_t(cells_pool.cell_height() * (1/move_step));
        size_t distance = (width + height) / 2;
        chrono::duration<int64_t, nano> time_step = move_time / distance;
        float adjusted_distance = distance / move_step;
        
        for(float i = move_step; i <= adjusted_distance; i += move_step) {
            chrono::time_point<chrono::steady_clock, chrono::nanoseconds>
            delay_start = chrono::steady_clock::now();
    
            if(body.front()->coord - destination != 1)
                continue;
            
            cout << "Start: " << endl;
            auto part = body.begin();
            Coord part_direction = destination - (*part)->coord;
            while(true) {
                // printPartPos;
                (*part)->filler->move(part_direction.x * move_step, part_direction.y * move_step);
                // printPartPos << endl;
                auto next_part = part++;
                if(part != body.end())
                    part_direction = (*next_part)->coord - (*part)->coord;
                else
                    break;
            }
            cout << "Stop." << endl << endl;
            
            while(chrono::steady_clock::now() - delay_start < time_step)
                ;
            cells_pool.display();
        }
    }
    
  private:
    list<Cell*> body;
    Coord direction = {0, 0};
    chrono::duration<int64_t, nano> move_time;
    queue<Coord> moves;
    chrono::time_point<chrono::steady_clock, chrono::nanoseconds>
    last_move = chrono::steady_clock::now();
    
    CellsPool& cells_pool;
};

class Game {
  public:
    Game(unsigned long width, unsigned long height,
          size_t count_cells_x, size_t count_cells_y,
          string FieldName)
    : settings(width / count_cells_x, height / count_cells_y)
    , window(sf::VideoMode(width, height), FieldName, sf::Style::Default)
    , cells_pool(count_cells_x, count_cells_y, window, settings)
    , snake(cells_pool)
    {
        size_t cell_width  = static_cast<size_t>(settings.default_rectangle.getSize().x);
        size_t cell_height = static_cast<size_t>(settings.default_rectangle.getSize().y);
        size_t normalized_size_x = cell_width  * count_cells_x;
        size_t normalized_size_y = cell_height * count_cells_y;
        window.create({normalized_size_x, normalized_size_y}, FieldName, sf::Style::Default);
        return;
    }
    
    void mainLoop() {
        try {
            while(window.isOpen()) {
                cells_pool.display();
                handle_events();
                snake.move();
            }
        } catch(CellsPool::NotFoundFreeCell const& e) {
    
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
    RectangleSettings settings;
    sf::RenderWindow window;
    CellsPool cells_pool;
    Snake snake;
};

int main() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    srand(static_cast<unsigned int>(time(0)));
    
    
    Game(500, 500, 25, 25, "Snake").mainLoop();
    return 0;
}