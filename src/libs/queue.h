#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include "node.h"

struct Queue{
    /// Pointer to the oldest added element.
    Node* first;        //la fel ca L.prim

    /// Pointer to the last element added.
    Node* last;         //La fel ca L.ultim

    /// The length of the queue.
    unsigned int size;

    /// Default constructor.
    Queue();

    /// Adds an element to the queue.
    void push(std::string element);

    /// Removes the oldest element from the queue.
    void pop();

    /// Returns the oldest element from the queue.
    std::string front();

    /// Returns whether the queue is empty or not.
    bool empty();
};


#endif // QUEUE_H_INCLUDED
