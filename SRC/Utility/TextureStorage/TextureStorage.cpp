//
// Created by Lyosha12 on 20.06.2018.
//

#include <boost/filesystem.hpp>
#include "TextureStorage.hpp"

TextureStorage::TextureStorage(std::vector<TextureParams> params) {
    for(auto const& param: params) {
        // Нужно создать текстуру прежде, чем загрузить её представление.
        textures.push_back({});
        
        boost::filesystem::path texture_path("../Resources/Textures/" + param.name);
        bool is_valid_path = boost::filesystem::exists(texture_path);
        bool is_loaded = textures.back().loadFromFile(texture_path.string());
        
        if(!is_valid_path || !is_loaded) {
            textures.pop_back();
            throw std::runtime_error("Could not found " + texture_path.string());
        }
        
        textures.back().setRepeated(param.is_repeated);
    }
}
TextureStorage::TextureStorage(TextureParams params)
: TextureStorage(std::vector{params})
{ }

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