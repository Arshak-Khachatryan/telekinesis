#include <../headers/queue.h>
#include <stdexcept>

template<class T, class Container> 
g3::queue<T, Container>::queue() = default;

template<class T, class Container> 
g3::queue<T, Container>::queue(const g3::queue<T, Container> &rhv):ob(rhv.ob){}

template<class T, class Container> 
g3::queue<T, Container>::queue(g3::queue<T, Container> &&rhv):ob(std::move(rhv.ob)){}

template<class T, class Container> 
g3::queue<T, Container>::queue(std::initializer_list<T> init):ob(init){}

template<class T, class Container> 
template<class InputIt> 
g3::queue<T, Container>::queue(InputIt first, InputIt last):ob(first,last){}

template<class T, class Container> 
g3::queue<T, Container>::~queue() = default;

template<class T, class Container> 
const g3::queue<T, Container> &g3::queue<T, Container>::operator=(const g3::queue<T, Container> &rhv){
    ob = rhv.ob;
    return *this;
}

template<class T, class Container> 
const g3::queue<T, Container> &g3::queue<T, Container>::operator=(g3::queue<T, Container> &&rhv){
    ob = std::move(rhv.ob);
    return *this;
}

template<class T, class Container> 
T &g3::queue<T, Container>::front(){
    if(empty()){
        throw std::out_of_range("Queue is empty");
    }
    return ob.front();
}

template<class T, class Container> 
const T &g3::queue<T, Container>::front() const{
    if(empty()){
        throw std::out_of_range("Queue is empty");
    }
    return ob.front();
}

template<class T, class Container> 
T &g3::queue<T, Container>::back(){
    if(empty()){
        throw std::out_of_range("Queue is empty");
    }
    return ob.back();
}

template<class T, class Container> 
const T &g3::queue<T, Container>::back() const{
    if(empty()){
        throw std::out_of_range("Queue is empty");
    }
    return ob.back();
}

template<class T, class Container> bool g3::queue<T, Container>::empty() const{
    return ob.empty();
}

template<class T, class Container> 
std::size_t g3::queue<T, Container>::size() const{
    return ob.size();
}

template<class T, class Container>
void g3::queue<T, Container>::push(const T &val){
    ob.push_back(val);
}

template<class T, class Container>
void g3::queue<T, Container>::pop(){
    ob.pop_front();
}

template<class T, class Container> 
bool g3::queue<T, Container>::operator==(const g3::queue<T, Container> &other) {
    return ob == other.ob;
}

template<class T, class Container> 
bool g3::queue<T, Container>::operator!=(const g3::queue<T, Container> &other) {
    return ob != other.ob;
}

template<class T, class Container> 
bool g3::queue<T, Container>::operator>=(const g3::queue<T, Container> &other) {
    return ob >= other.ob;
}

template<class T, class Container> 
bool g3::queue<T, Container>::operator<=(const g3::queue<T, Container> &other) {
    return ob <= other.ob;
}

template<class T, class Container> 
bool g3::queue<T, Container>::operator>(const g3::queue<T, Container> &other) {
    return ob > other.ob;
}

template<class T, class Container> 
bool g3::queue<T, Container>::operator<(const g3::queue<T, Container> &other) {
    return ob < other.ob;
}