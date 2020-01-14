#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <string>

/// Binary tree definition.
struct BinaryTree{
    /// The string stored in this tree node.
    std::string data;

    /// The left subtree.
    BinaryTree* left;

    /// The right subtree.
    BinaryTree* right;

    /// Default constructor.
    BinaryTree();

    /// Returns a copy of the tree.
    BinaryTree* copy();
};

/// Tree node definition (holds a binary tree as data).
struct TreeNode {
    /// Holds information.
    BinaryTree* data;

    /// Pointer to the next node.
    TreeNode* next;

    /// Default constructor.
    TreeNode();
};

#endif // TREE_H_INCLUDED
