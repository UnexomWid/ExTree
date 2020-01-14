#ifndef TREE_QUEUE_H_INCLUDED
#define TREE_QUEUE_H_INCLUDED

#include "tree.h"
#include "definitions.h"

/// Represents a queue of binary trees.
struct TreeQueue {
    /// The pointer to the oldest element.
    TreeNode* first;

    /// The pointer to the newest element.
    TreeNode* last;

    /// The size of the queue.
    uint size;

    /// Default constructor.
    TreeQueue();

    /// Adds an element to the queue.
    void push(BinaryTree* element);

    /// Removes the oldest element from the queue.
    void pop();

    /// Returns the oldest element from the queue.
    BinaryTree* front();

    /// Returns whether or not the queue is empty.
    bool empty();

    /// Returns a copy of the queue.
    TreeQueue copy();
};


#endif // TREE_QUEUE_H_INCLUDED
