#include "stack.h"

Stack::Stack(){
    size = 0;
    first = new Node;
}
void Stack::push(std::string element) {
    Node* node = new Node;
    node->data = element;
    node->next = first;
    first = node;

    ++size;
}

std::string Stack::top() {
    if(size) return first->data;

    std::string emptyString;
    return emptyString;
}

void Stack::pop() {
    if(size == 0) return;

    Node* node = new Node;
    node = first;
    first = first->next;
    delete node;

    --size;
}

bool Stack::empty() {
    return size == 0;
}
