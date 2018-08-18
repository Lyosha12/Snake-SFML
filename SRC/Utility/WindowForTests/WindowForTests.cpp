// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 18.05.2018.
//

#include <thread>

#include "WindowForTests.hpp"

WindowForTests::
WindowForTests(sf::VideoMode screen, sf::Drawable const& drawable)
: mode_for_test(
    static_cast<unsigned>(screen.width*scale_input),
    static_cast<unsigned>(screen.height*scale_input)
  )
, window(mode_for_test, "Test Window")
, drawable(drawable)
{ window.setFramerateLimit(30); }

void WindowForTests::
run() {
    while(window.isOpen()) {
        handling_events();
        draw();
    }
}


void WindowForTests::
handling_events() {
    sf::Event event;
    while(window.pollEvent(event)) {
        switch(event.type) {
            case sf::Event::EventType::Closed:
                window.close();
                break;
            
            default:
                break;
        }
    }
}

void WindowForTests::
draw() {
    window.clear({128, 128, 128});
    window.draw(drawable, sf::Transform().translate(window.getSize().x/15, window.getSize().y/15));
    window.display();
}