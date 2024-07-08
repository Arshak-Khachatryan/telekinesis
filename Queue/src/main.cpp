#include "../headers/queue.h"
#include <iostream>
#include <vector>

int main(){
    g3::queue<int, std::deque<int>> q;

    q.push(10);
    q.push(20);
    q.push(30);

    std::cout << "Front element: " << q.front() << std::endl;
    std::cout << "Back element: " << q.back() << std::endl;

    q.pop();

    std::cout << "Front element after pop: " << q.front() << std::endl;
    std::cout << "Back element after pop: " << q.back() << std::endl;

    std::cout << "Queue is empty: " << (q.empty() ? "true" : "false") << std::endl;

    std::cout << "Queue size: " << q.size() << std::endl;

    g3::queue<int, std::deque<int>> q2;
    q2 = q;

    std::cout << "Front element of q2: " << q2.front() << std::endl;
    std::cout << "Back element of q2: " << q2.back() << std::endl;

    std::cout << "q == q2: " << (q == q2 ? "true" : "false") << std::endl;
    return 0;
}