#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include "node.h"
#include "definitions.h"

/// Represents a queue of strings.
struct Queue {
    /// The pointer to the oldest element.
    Node* first;

    /// The pointer to the newest element.
    Node* last;

    /// The size of the queue.
    uint size;

    /// Default constructor.
    Queue();

    /// Adds an element to the queue.
    void push(std::string element);

    /// Removes the oldest element from the queue.
    void pop();

    /// Returns the oldest element from the queue.
    std::string front();

    /// Returns whether or not the queue is empty.
    bool empty();

    /// Returns a copy of the queue.
    Queue copy();
};


#endif // QUEUE_H_INCLUDED
