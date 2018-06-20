//
// Created by Lyosha12 on 20.06.2018.
//

#include "TextureStorage.hpp"

TextureStorage::TextureStorage(std::vector<std::string> texture_names) {
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
TextureStorage::TextureStorage(std::string texture_name, bool is_repeated) {
    textures.push_back({});
    
    if(!textures.back().loadFromFile("Textures/" + texture_name))
        throw std::runtime_error(
            "Texture " +
            texture_name +
            " was not loaded from Textures/"
        );
    
    textures[0].setRepeated(is_repeated);
}

sf::Texture const& TextureStorage::operator[] (size_t texture_index) const {
    if(texture_index < textures.size())
        return textures[texture_index];
    else
        throw std::logic_error(
            "Try to use uncreated texture: " +
            std::to_string(texture_index)
        );
}

TextureStorage::operator sf::Texture const& () const {
    if(textures.size() == 1)
        return textures[0];
    else
        throw std::logic_error(
            "Try to use list of textures as single texture"
        );
}
sf::Texture const* TextureStorage::operator-> () const {
    return &static_cast<sf::Texture const&> (*this);
}