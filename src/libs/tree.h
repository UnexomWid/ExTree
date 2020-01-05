#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <string>

/// Binary tree definition.
struct BinaryTree{
    /// This holds the information within the node.
    std::string data;

    /// Pointer to the left child.
    BinaryTree* left;

    /// Pointer to the right child.
    BinaryTree* right;

    ///Pointer to parent.
    BinaryTree* parent;

    /// Default constructor.
    BinaryTree();
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
