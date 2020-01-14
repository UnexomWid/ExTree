#include "tree_queue.h"

TreeQueue::TreeQueue(){
    size = 0;
    first = new TreeNode;
    last =  new TreeNode;
}

void TreeQueue::push(BinaryTree* element)
{
    TreeNode* node = new TreeNode;
    node->data = element;
    if(size == 0)
    {
        first = last = node;
        ++size;
        return;
    }
    last->next = node;
    last = node;

    ++size;
}

void TreeQueue::pop()
{
    if(size == 0) return;

    TreeNode* node = first;
    first = first->next;
    delete node;
    --size;
}

BinaryTree* TreeQueue::front()
{
    if(size > 0) return first->data;

    return nullptr;
}

bool TreeQueue::empty()
{
    return size == 0;
}

TreeQueue TreeQueue::copy() {
    TreeQueue queue;
    TreeNode* n = first;
    for(unsigned int i = 0; i < size; ++i, n = n->next)
        queue.push(n->data);

    return queue;
}
