//
// Created by Lyosha12 on 24.06.2018.
//

#ifndef SNAKE_LISTRUNNER_HPP
#define SNAKE_LISTRUNNER_HPP

#include <list>

template <class T>
static typename std::list<T>::iterator forward(std::list<T>& list, size_t requested) {
    auto element = list.begin();
    for(size_t i = 0; i != requested; ++i)
        ++element;
    return element;
}

template <class T>
static typename std::list<T>::iterator backward(std::list<T>& list, size_t requested) {
    auto element = list.end();
    for(size_t i = requested + 1; i != requested; --i)
        --element;
    return element;
}

// Позволяет использовать индексирование для списка.
// FIXME: Может, сделать класс-обёртку?
template <class T>
typename std::list<T>::iterator getListElement(std::list<T>& list, size_t requested) {
    bool is_on_left = requested <= list.size() / 2;
    
    return is_on_left ? forward(list, requested) : backward(list, requested);
}

#endif //SNAKE_LISTRUNNER_HPP
