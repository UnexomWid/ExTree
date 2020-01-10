#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "node.h"

struct Stack{
    Node* first;

    /// The size of the stack.
    unsigned int size;

    Stack();

    void push(std::string element);

    void pop();

    std::string top();

    bool empty();
};
#endif // STACK_H_INCLUDED
