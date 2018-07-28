//
// Created by Lyosha12 on 20.06.2018.
//

#include "TextureStorage.hpp"

TextureStorage::TextureStorage(std::vector<TextureParams> params) {
    for(auto const& param: params) {
        textures.push_back({});
        if(!textures.back().loadFromFile("Resources/Textures/" + param.name)) {
            textures.pop_back();
            throw std::runtime_error(
                "Texture " +
                param.name +
                " was not loaded from Resources/Textures/"
            );
        }
        
        textures.back().setRepeated(param.is_repeated);
    }
}
TextureStorage::TextureStorage(TextureParams params): TextureStorage(std::vector{params}) { }

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