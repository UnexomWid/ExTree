#ifndef TREE_STACK_H_INCLUDED
#define TREE_STACK_H_INCLUDED

#include "tree.h"
#include "definitions.h"

/// Represents a stack of binary trees.
struct TreeStack {
    /// The pointer to the newest element.
    TreeNode* first;

    /// The size of the stack.
    uint size;

    /// Default constructor.
    TreeStack();

    /// Adds an element to the stack.
    void push(BinaryTree* element);

    /// Removes the newest element from the stack.
    void pop();

    /// Returns the newest element from the stack.
    BinaryTree* top();

    /// Returns whether or not the stack is empty.
    bool empty();
};

#endif // TREE_STACK_H_INCLUDED
