#include "../headers/stack.h"
#include <iostream>

void test_stack() {
    g3::stack<int> myStack;
    std::cout << "Testing stack of integers..." << std::endl;

    std::cout << "Initial stack is empty: " << std::boolalpha << myStack.empty() << std::endl;

    myStack.push(10);
    myStack.push(20);
    myStack.push(30);

    std::cout << "Top element after three pushes: " << myStack.top() << std::endl;

    myStack.pop();
    std::cout << "Top element after one pop: " << myStack.top() << std::endl;

    std::cout << "Size of stack: " << myStack.size() << std::endl;

    std::cout << "Stack is empty: " << std::boolalpha << myStack.empty() << std::endl;

    myStack.pop();
    myStack.pop();
    std::cout << "Stack is empty after popping all elements: " << std::boolalpha << myStack.empty() << std::endl;
    
    try {
        myStack.pop();
    } catch (const std::out_of_range& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    try {
        myStack.top();
    } catch (const std::out_of_range& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}

int main() {
    test_stack();
    return 0;
}
