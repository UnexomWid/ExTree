#include "queue.h"

Queue::Queue(){
    length = 0;
    first = new Node;
    last =  new Node;
}

void Queue::add(std::string element)
{
    Node* node = new Node;
    node->data = element;
    if(length == 0)
    {
        first = last = node;
        ++length;
        return;
    }
    last->next = node;
    last = node;

    ++length;
}

void Queue::removeFirst()
{
    if(length == 0) return;

    Node* node = new Node;
    node = first;
    first = first->next;
    delete node;
    --length;
}

std::string Queue::returnFirst()
{
    if(length > 0) return first->data;

    std::string emptyString;
    return emptyString;
}

bool Queue::isEmpty()
{
    if(length == 0) return true;
    return false;
}
