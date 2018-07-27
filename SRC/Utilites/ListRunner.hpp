//
// Created by Lyosha12 on 24.06.2018.
//

#ifndef SNAKE_LISTRUNNER_HPP
#define SNAKE_LISTRUNNER_HPP

#include <list>


template <class T>
using ListIter = typename std::_List_iterator<T>;
template <class T>
using List = std::list<T>;


template <class T, class Integer>
static ListIter<T> forward(List<T>& list, Integer requested) {
    auto element = list.begin();
    for(size_t i = 0; i != requested; ++i)
        ++element;
    return element;
}

template <class T, class Integer>
static ListIter<T> backward(List<T>& list, Integer requested) {
    auto element = list.end() - 1;
    for(size_t i = list.size() - 1; i != requested; --i)
        --element;
    return element;
}

// Позволяет использовать индексирование для списка.
// FIXME: Может, сделать класс-обёртку?
template <class T, class Integer>
ListIter<T> getListElement(List<T>& list, Integer requested) {
    bool is_on_left = requested <= list.size() / 2;
    
    return is_on_left ? forward(list, requested) : backward(list, requested);
}




// Операторы перемещения по списку.
template <class T, class Integer>
ListIter<T> operator+ (ListIter<T> i, Integer x) {
    while(x--) {
        ++i;
    }
    
    return i;
}
template <class T, class Integer>
ListIter<T> operator- (ListIter<T> i, Integer x) {
    while(x--) {
        --i;
    }
    
    return i;
}


#endif //SNAKE_LISTRUNNER_HPP
