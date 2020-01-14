#include "tree.h"

BinaryTree::BinaryTree() {
    left = nullptr;
    right = nullptr;
}

BinaryTree* BinaryTree::copy() {
    BinaryTree* tree = new BinaryTree;

    tree->data = data;
    if(left != nullptr)
        tree->left = left->copy();
    else tree->left = nullptr;

    if(right != nullptr)
        tree->right = right->copy();
    else tree->right = nullptr;

    return tree;
}

TreeNode::TreeNode() {
    next = nullptr;
}
