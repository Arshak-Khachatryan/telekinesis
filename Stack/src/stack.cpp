#ifndef _STACK_HPP_
#define _STACK_HPP_

#include "../headers/stack.h"
#include <stdexcept>

template<class T, class Container> 
g3::stack<T, Container>::stack() {}

template<class T, class Container>
g3::stack<T, Container>::stack(const g3::stack<T, Container> &rhv) : ob(rhv.ob) {}

template<class T, class Container> 
g3::stack<T, Container>::stack(g3::stack<T, Container> &&rhv) : ob(std::move(rhv.ob)) {}

template<class T, class Container> 
g3::stack<T, Container>::stack(std::initializer_list<T> init) : ob(init) {}

template<class T, class Container> 
template<class InputIt>
g3::stack<T, Container>::stack(InputIt first, InputIt last) : ob(first, last) {}

//----
template<class T, class Container> 
g3::stack<T, Container>::~stack() {}
//----

template<class T, class Container> 
const g3::stack<T, Container> &g3::stack<T, Container>::operator=(const g3::stack<T, Container> &rhv) {
    ob = rhv.ob;
    return *this;
}

template<class T, class Container>
const g3::stack<T, Container> &g3::stack<T, Container>::operator=(g3::stack<T, Container> &&rhv) {
    ob = std::move(rhv.ob);
    return *this;
}

template<class T, class Container> 
T &g3::stack<T, Container>::top() {
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    }
    return ob.back();
}

template<class T, class Container> 
const T &g3::stack<T, Container>::top() const {
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    }
    return ob.back();
}

template<class T, class Container> 
bool g3::stack<T, Container>::empty() const {
    return ob.empty();
}

template<class T, class Container> 
std::size_t g3::stack<T, Container>::size() const {
    return ob.size();
}

template<class T, class Container>
void g3::stack<T, Container>::push(const T &val) {
    ob.push_back(val);
}

template<class T, class Container> 
void g3::stack<T, Container>::pop() {
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    }
    ob.pop_back();
}

template<class T, class Container> 
bool g3::stack<T, Container>::operator==(const g3::stack<T, Container> &other) {
    return ob == other.ob;
}

template<class T, class Container> 
bool g3::stack<T, Container>::operator!=(const g3::stack<T, Container> &other) {
    return ob != other.ob;
}

template<class T, class Container> 
bool g3::stack<T, Container>::operator>=(const g3::stack<T, Container> &other) {
    return ob >= other.ob;
}

template<class T, class Container> 
bool g3::stack<T, Container>::operator<=(const g3::stack<T, Container> &other) {
    return ob <= other.ob;
}

template<class T, class Container> 
bool g3::stack<T, Container>::operator>(const g3::stack<T, Container> &other) {
    return ob > other.ob;
}

template<class T, class Container> 
bool g3::stack<T, Container>::operator<(const g3::stack<T, Container> &other) {
    return ob < other.ob;
}

#endif
