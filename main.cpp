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
#include <windows.h>
using namespace std;
#include <SFML/Graphics.hpp>

#include "ErrorPrinter/ErrorPrinter.hpp"

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
    Coord(int x, int y): x(x), y(y) { }
    Coord(size_t x, size_t y): x(x), y(y) { }
    
    
    double vectorLength() const {
        return sqrt(x*x + y*y);
    }
    
    bool  operator== (double value) const {
        return abs(vectorLength() - value) < 1e-5;
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
class Snake;
class DefaultRectangle {
    // Создание стандартного прямоугольника на поле.
    // В процессе игры он переиспользуется для создания других клеток.
    
  public:
    DefaultRectangle(float cell_width, float cell_height)
        : rect({cell_width, cell_height})
    { rect.setFillColor(MyColors::royal_blue); }

    class Configurator {
        // У любого прямоугольника поля есть позиция,
        // цвет и масштаб относительно других прямоугольников.
        // Класс определяет на поле конкретный прямоугольник из стандартного.

        friend DefaultRectangle;
    public:
        Configurator(Coord pos_on_field, sf::Texture const& texture)
            : pos_on_field(pos_on_field)
            , texture(texture)
        { }
      
      private:
        sf::Sprite operator() (sf::RectangleShape const& default_rectangle) const {
            sf::Sprite sprite(texture);
            setPos(sprite, default_rectangle);
           
            return sprite;
        }

        void setPos(sf::Sprite& sprite, sf::RectangleShape const& default_rectangle) const {
            // В соответствии с текущими настройками
            // устанавливается позиция для переданного прямоугольника.
            float width  = default_rectangle.getSize().x;
            float height = default_rectangle.getSize().y;
            sprite.setPosition(width * pos_on_field.x, height * pos_on_field.y);
        }
      
      private:
        Coord pos_on_field;
        sf::Texture const& texture;
    };
    
    sf::Sprite configure(Configurator const& configurator) const {
        // Создание по указанным настройкам прямоугольника для игрового поля.
        return configurator(rect);
    }
    
    
    sf::RectangleShape rect;
};

class Cell: public sf::Drawable {
    // Представляет клетку на поле.
    // Клетка имеет координаты, возможность
    // быть использованной(usable) или нет.
    // Имеет заполнитель - то, чем она является.
    // Заполнитель контролирует бассейн клеток (cells_pool).
    
  public:
    class Filler: public sf::Drawable {
      // Заполнитель клетки - это некий спрайт.
      // Его текстуру и форму определяет наследник этого класса.
    
      // Каждую клетку змейка может занять.
      // И, в зависимости от реализации функции modifer,
      // змейка будет изменена так или иначе.
      public:
        Filler(sf::Sprite sprite) : sprite(sprite) { }
        virtual void modifer(Snake&) const { }
        
      private:
        sf::Sprite sprite;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override  {
            target.draw(sprite, states);
        }
    };
    
  public:
    Cell() = default;
    Cell(Cell&& cell)
    : coord(cell.coord)
    , filler(move(cell.filler))
    , is_usable(cell.is_usable)
    { }
    
    Coord coord = {-1, -1};
    unique_ptr<Filler> filler = nullptr;
    bool is_usable = false;
    
  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override  {
        target.draw(*filler, states);
    }
};


class TextureStorage {
  // Хранит один экземпляр(ы) текстуры для каждого типа клетки статически.
  
  public:
    TextureStorage(std::vector<std::string> texture_names) {
        for(auto const& name: texture_names) {
            textures.push_back({});
            if(!textures.back().loadFromFile("Textures/" + name))
                throw std::runtime_error(
                    "Texture " +
                    name +
                    " was not loaded from Textures/"
                );
        }
    }
    TextureStorage(const char* texture_name): TextureStorage(std::string(texture_name)) { }
    TextureStorage(std::string texture_name) {
        textures.push_back({});
        if(!textures.back().loadFromFile("Textures/" + texture_name))
            throw std::runtime_error(
                "Texture " +
                texture_name +
                " was not loaded from Textures/"
            );
    
    }
  
  sf::Texture const& operator() (size_t texture_index) {
      if(texture_index < textures.size())
          return textures[texture_index];
      else
          throw std::logic_error(
              "Try to use uncreated texture: " +
              std::to_string(texture_index)
          );
  }
  operator sf::Texture const& () {
      if(textures.size() == 1)
          return textures[0];
      else
          throw std::logic_error("Try to use list of textures as single texture");
  }
  
  private:
    std::vector<sf::Texture> textures;
};

class FreeCell: public Cell::Filler {
  public:
    FreeCell(DefaultRectangle const& default_rectangle, Cell& cell, Coord const& coord)
        : Filler(createSprite(default_rectangle, cell.coord = coord))
    { cell.is_usable = true; }
    FreeCell(DefaultRectangle const& default_rectangle, Cell& cell)
        : Filler(createSprite(default_rectangle, cell.coord))
    { cell.is_usable = true; }
    
    
    sf::Sprite createSprite(DefaultRectangle const& default_rectangle, Coord const& coord) const {
        return default_rectangle.configure(DefaultRectangle::Configurator(coord, texture));
    }
  
  private:
    inline static TextureStorage texture = "Background.png";
};
class SnakeHead: public Cell::Filler {
  public:
    SnakeHead(DefaultRectangle const& default_rectangle, Cell& cell)
    : Filler(createSprite(default_rectangle, cell.coord))
    { cell.is_usable = false; }

    
    sf::Sprite createSprite(DefaultRectangle const& default_rectangle, Coord const& coord) const {
        return default_rectangle.configure(DefaultRectangle::Configurator(coord, texture));
    }
  
  private:
    inline static TextureStorage texture = "Head.png";
};
class SnakeBody: public Cell::Filler {
  public:
    SnakeBody(DefaultRectangle const& default_rectangle, Cell& cell)
    : Filler(createSprite(default_rectangle, cell.coord))
    { cell.is_usable = false; }
    
    sf::Sprite createSprite(DefaultRectangle const& default_rectangle, Coord const& coord) const {
        return default_rectangle.configure(DefaultRectangle::Configurator(coord, texture));
    }
  
  private:
    inline static TextureStorage texture = "Body.png";
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
              sf::RenderWindow& window, DefaultRectangle const& settings)
    : default_rectangle(settings)
    , count_cells_x(count_cells_x)
    , count_cells_y(count_cells_y)
    , window(window)
     {
         cells.resize(count_cells_y);
         for(auto& row: cells)
             row = move(vector<Cell>(count_cells_x));
         
         for(size_t y = 0; y != count_cells_y; ++y)
            for(size_t x = 0; x != count_cells_x; ++x) {
                cells[y][x].filler.reset(new FreeCell(
                    default_rectangle,
                    cells[y][x],
                    Coord(x, y)
                ));
                available_cells.push_back(&cells[y][x]);
            }
    }
    
    template <class Filler>
    Cell* getRandCell() {
        size_t i = 0;
        size_t rand_cell = rand()%available_cells.size();
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
        vector<Cell*> neighbors = {up, down, right, left};
        
        while(!neighbors.empty()) {
            size_t rand_neighbor = rand()%neighbors.size();
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
        cell->filler.reset(new FreeCell(default_rectangle, *cell));
        available_cells.push_front(cell);
    }
    
    void display() const {
        window.clear(default_rectangle.rect.getFillColor());
        
        for(auto const& row: cells)
            for(auto const& cell: row)
                window.draw(cell);
        
        window.display();
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
    Cell* kickFromAvailable(list<Cell*>::iterator runner, Cell::Filler* filler) {
        // Выбросить клетку из свободных и
        // обновить её содержание новым заполнителем.
        Cell* cell = *runner;
        available_cells.erase(runner);
        cell->filler.reset(filler);
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
  
  private:
    DefaultRectangle const& default_rectangle;
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
        if(chrono::steady_clock::now() - last_move < move_time)
           return;
        last_move = chrono::steady_clock::now();
        tryChangeDirection();
    
        auto new_head = cells_pool.getNearCell<SnakeHead>(body.front(), direction);
        
        cells_pool.releaseCell(body.front());
        body.push_front(cells_pool.getNearCell<SnakeBody>(body.front(), {0, 0}));
        body.pop_front();
        
        body.push_front(new_head);
        
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
    list<Cell*> body;
    Coord direction = {0, 0};
    chrono::duration<int64_t, nano> move_time;
    queue<Coord> moves;
    chrono::time_point<chrono::steady_clock, chrono::nanoseconds>
    last_move = chrono::steady_clock::now();
    
    CellsPool& cells_pool;
};

class Game {
    // Главный класс. Управляет игровым циклом и отрисовкой.
    
  public:
    Game(unsigned long width, unsigned long height,
          size_t count_cells_x, size_t count_cells_y,
          string FieldName)
    : settings(width / count_cells_x, height / count_cells_y)
    , window(sf::VideoMode(width, height), FieldName, sf::Style::Default)
    , cells_pool(count_cells_x, count_cells_y, window, settings)
    , snake(cells_pool)
    {
        size_t cell_width  = static_cast<size_t>(settings.rect.getSize().x);
        size_t cell_height = static_cast<size_t>(settings.rect.getSize().y);
        size_t normalized_size_x = cell_width  * count_cells_x;
        size_t normalized_size_y = cell_height * count_cells_y;
        window.create({normalized_size_x, normalized_size_y}, FieldName, sf::Style::Default);
        return;
    }
    
    void mainLoop() {
        try {
            while(window.isOpen()) {
                cells_pool.display(); // Отрисовываем все клетки поля.
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
    DefaultRectangle settings;
    sf::RenderWindow window;
    CellsPool cells_pool;
    Snake snake;
};

int main() {
    // Настройка "окружения".
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    srand(static_cast<unsigned int>(time(0)));
    
    Game(500, 500, 25, 25, "Snake").mainLoop();
    return 0;
}
