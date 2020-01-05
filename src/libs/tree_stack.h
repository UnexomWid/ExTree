#ifndef TREE_STACK_H_INCLUDED
#define TREE_STACK_H_INCLUDED

#include "tree.h"

struct TreeStack {
    TreeNode* first;

    /// The size of the stack.
    unsigned int size;

    TreeStack();

    void push(BinaryTree* element);

    void pop();

    BinaryTree* top();

    bool empty();
};

#endif // TREE_STACK_H_INCLUDED
