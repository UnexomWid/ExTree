#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "node.h"
#include "definitions.h"

/// Represents a stack of strings.
struct Stack {
    /// The pointer to the newest element.
    Node* first;

    /// The size of the stack.
    uint size;

    /// Default constructor.
    Stack();

    /// Adds an element to the stack.
    void push(std::string element);

    /// Removes the newest element from the stack.
    void pop();

    /// Returns the newest element from the stack.
    std::string top();

    /// Returns whether or not the stack is empty.
    bool empty();
};

#endif // STACK_H_INCLUDED
