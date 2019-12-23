#include "stack.h"

Stack::Stack(){
    length = 0;
    first = new Node;
}
void Stack::push(std::string element)
{
    Node* node = new Node;
    node->data = element;
    node->next = first;
    first = node;

    ++length;
}

std::string Stack::top()
{
    if(length) return first->data;

    std::string emptyString;
    return emptyString;
}

void Stack::pop()
{
    if(length == 0) return;

    Node* node = new Node;
    node = first;
    first = first->next;
    delete node;

    --length;
}

bool Stack::isEmpty()
{
    return length == 0;
}
