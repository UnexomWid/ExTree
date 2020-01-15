#include "tree_stack.h"

TreeStack::TreeStack(){
    size = 0;
    first = nullptr;
}
void TreeStack::push(BinaryTree* element) {
    TreeNode* node = new TreeNode;

    node->data = element;
    node->next = first;
    first = node;

    ++size;
}

BinaryTree* TreeStack::top() {
    if(size > 0) return first->data;

    BinaryTree* emptyString;
    return emptyString;
}

void TreeStack::pop() {
    if(size == 0) return;

    TreeNode* node = first;
    first = first->next;
    delete node;

    --size;
}

bool TreeStack::empty() {
    return size == 0;
}
