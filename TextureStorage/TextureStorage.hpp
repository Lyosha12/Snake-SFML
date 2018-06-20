//
// Created by Lyosha12 on 20.06.2018.
//

#ifndef SNAKE_TEXTURESTORAGE_HPP
#define SNAKE_TEXTURESTORAGE_HPP

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

class TextureStorage {
  // ������ ���� ���������(�) �������� ��� ������� ���� ������ ����������.
  
  public:
    // ������������, ����������� ��������� �������� �� ����� Textures/
    TextureStorage(std::vector<std::string> texture_names);
    TextureStorage(std::string texture_name, bool is_repeated = false);
    
    // ������ ���������� ��������.
    sf::Texture const& operator[] (size_t texture_index) const;
    
    // �������� ��� �������� ������ ����� ��������.
    operator sf::Texture const& () const;
    
    // ������ ������������ ���������� ��������.
    sf::Texture const* operator-> () const;
    
    
  private:
    std::vector<sf::Texture> textures;
};


#endif //SNAKE_TEXTURESTORAGE_HPP
