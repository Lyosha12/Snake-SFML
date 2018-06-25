//
// Created by Lyosha12 on 24.06.2018.
//

#include "Body.hpp"

Body::Body(DefaultRectangle const& default_rectangle, Coord const& coord,
           std::function<std::unique_ptr<Bonus>(Snake&)> bonus_creator)
    : Filler(default_rectangle, coord, texture, false, std::move(bonus_creator))
{ }