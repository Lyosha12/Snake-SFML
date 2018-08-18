//
// Created by Lyosha12 on 24.06.2018.
//

#ifndef SNAKE_LISTRUNNER_HPP
#define SNAKE_LISTRUNNER_HPP

#include <list>

template <class T>  using List           = std::list<T>;
template <class T>  using ListIter       = typename std::_List_iterator<T>;
template <class T>  using ConstListIter  = typename std::_List_const_iterator<T>;


template <class T>
static ConstListIter<T> forward(List<T> const& list, size_t requested) {
    ConstListIter<T> element = list.cbegin();
    for(size_t i = 0; i != requested; ++i)
        ++element;
    return element;
}
template <class T>
static ConstListIter<T> backward(List<T> const& list, size_t requested) {
    ConstListIter<T> element = list.cend() - 1;
    for(size_t i = list.size() - 1; i != requested; --i)
        --element;
    return element;
}



// Позволяет использовать индексирование для списка.
template <class T>
ConstListIter<T> getListElement(List<T> const& list, size_t requested) {
    bool is_on_left = requested <= list.size() / 2;
    
    return is_on_left ? forward(list, requested) : backward(list, requested);
}
template <class T>
ListIter<T> getListElement(List<T>& list, size_t requested) {
    ConstListIter<T> found = getListElement(const_cast<List<T> const&>(list), requested);
    // https://stackoverflow.com/a/10669041/9742885
    return list.erase(found, found);
}






// Операторы перемещения по списку.
template <class T>
ConstListIter<T> operator+ (ConstListIter<T> i, size_t x) {
    while(x--) {
        ++i;
    }
    
    return i;
}
template <class T>
ConstListIter<T> operator- (ConstListIter<T> i, size_t x) {
    while(x--) {
        --i;
    }
    
    return i;
}


#endif //SNAKE_LISTRUNNER_HPP
