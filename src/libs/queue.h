#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include "node.h"

struct Queue{
    /// Pointer to the oldest added element.
    Node* first;        //la fel ca L.prim

    /// Pointer to the last element added.
    Node* last;         //La fel ca L.ultim

    /// The length of the queue.
    unsigned int length;

    /// Default constructor.
    Queue();

    /// Adds an element to the queue.
    void add(std::string element);

    /// Removes the oldest element from the queue.
    void removeFirst();

    /// Returns the oldest element from the queue.
    std::string returnFirst();

    /// Returns whether the queue is empty or not.
    bool isEmpty();
};


#endif // QUEUE_H_INCLUDED
