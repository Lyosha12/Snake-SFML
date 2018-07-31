//
// Created by Lyosha12 on 20.06.2018.
//

#ifndef SNAKE_TEXTURESTORAGE_HPP
#define SNAKE_TEXTURESTORAGE_HPP

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

class TextureStorage {
  // Хранит один экземпляр(ы) текстуры для каждого типа клетки статически.
  
  public:
    struct TextureParams {
        std::string name;
        bool is_repeated;
        // TODO: Трансформации, необходимые для нормальных текстур змейки.
    };
    
    
    // Конструкторы, загружающие указанные текстуры из папки Textures/
    TextureStorage(std::vector<TextureParams> params);
    TextureStorage(TextureParams params);
    
    // Выдать конкретную текстуру.
    sf::Texture const& operator[] (size_t texture_index) const;
    
    // Работает при хранении только одной текстуры.
    operator sf::Texture const& () const;
    
    // Выдать единственную хранящуюся текстуру.
    sf::Texture const* operator-> () const;
    
    
  private:
    std::vector<sf::Texture> textures;
};


#endif //SNAKE_TEXTURESTORAGE_HPP
