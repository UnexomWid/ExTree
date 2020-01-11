#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <string>

/// Represents a binary tree.
struct BinaryTree {
    /// The string stored in this tree node.
    std::string data;

    /// The pointer to the left subtree.
    BinaryTree* left;

    /// The pointer to the right subtree.
    BinaryTree* right;

    /// Default constructor.
    BinaryTree();
};

/// Represents a simple linked list node that stores a binary tree.
struct TreeNode {
    /// The binary tree stored in this node.
    BinaryTree* data;

    /// The pointer to the next node.
    TreeNode* next;

    /// Default constructor.
    TreeNode();
};

#endif // TREE_H_INCLUDED
