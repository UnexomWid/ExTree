#include "tree.h"

Tree::Tree()
{
    length = 0;
    root = new treeNode;
}

void Tree::insertNode(treeNode* parentNode, std::string element)
{
    treeNode node = new treeNode;
    node->data = element;
    if(length == 0)
    {
        root = node;
        node->parent = root;
        ++length;
        return;
    }
    if(parentNode->left == nullptr)
    {
        parentNode->left = node;
        node->parent = parentNode;
        ++length;
    }
    else
        if(parentNode->right == nullptr)
        {
            parentNode->right = node;
            node->parent = parentNode;
            ++length;
        }
}

void Tree::deleteNode(treeNode* node)
{
    if(node->left == nullptr && node->right == nullptr)
    {
        --length;
        delete node;
    }
}

bool Tree::isEmpty()
{
    return length == 0;
}
