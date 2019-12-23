#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

struct treeNode{
    /// This holds the information within the node.
    std::string data;

    /// Pointer to the left child.
    treeNode* left;

    /// Pointer to the right child.
    treeNode* right;

    ///Pointer to parent.
    treeNode* parent;

    /// Default constructor.
    treeNode()
    {
        left = new treeNode;
        right = new treeNode;
        parent = new treeNode;
    }
};

struct Tree{
    /// The root of the tree.
    treeNode* root;

    /// The amount of elements in the tree.
    unsigned int lenght;

    /// Default constructor.
    Tree();

    /// Inserts a new node as a child of the specified node.
    void insertNode(treeNode* parentNode, std::string element);

    /// Deletes a node ONLY IF it has no children.
    void deleteNode(treeNode* node);

    /// Returns whether the tree is empty or not.
    bool isEmpty();
};

#endif // TREE_H_INCLUDED
