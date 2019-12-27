#include "tree.h"

Tree::Tree()
{
    lenght = 0;
    root = new treeNode;
}

void Tree::insertNode(treeNode* parentNode, std::string element)
{
    treeNode* node = new treeNode;
    node->data = element;
    if(lenght == 0)
    {
        root = node;
        node->parent = root;
        ++lenght;
        return;
    }
    if(parentNode->left == nullptr)
    {
        parentNode->left = node;
        node->parent = parentNode;
        ++lenght;
    }
    else
        if(parentNode->right == nullptr)
        {
            parentNode->right = node;
            node->parent = parentNode;
            ++lenght;
        }
}

void Tree::deleteNode(treeNode* node)
{
    if(node->left == nullptr && node->right == nullptr)
    {
        --lenght;
        delete node;
    }
}

bool Tree::isEmpty()
{
    return lenght == 0;
}
