//
// Created by Lyosha12 on 18.05.2018.
//

#include <thread>

#include "WindowForTests.hpp"

WindowForTests::
WindowForTests(sf::VideoMode screen, sf::Drawable const& drawable)
: window({screen.width*1.15, screen.height*1.15}, "Test Window")
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