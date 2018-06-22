//
// Created by Lyosha12 on 18.06.2018.
//

#include "DefaultRectangle.hpp"

DefaultRectangle::DefaultRectangle(float cell_width, float cell_height)
    : default_rectangle({cell_width, cell_height})
{ }

sf::Sprite DefaultRectangle::
configure(Configurator const& configurator) const {
    // Создание по указанным настройкам прямоугольника для игрового поля.
    return configurator(default_rectangle);
}

sf::Vector2f DefaultRectangle::getSize() const {
    return default_rectangle.getSize();
}


