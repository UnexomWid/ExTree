#include "queue.h"

Queue::Queue(){
    size = 0;
    first = new Node;
    last =  new Node;
}

void Queue::push(std::string element)
{
    Node* node = new Node;
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

void Queue::pop()
{
    if(size == 0) return;

    Node* node = new Node;
    node = first;
    first = first->next;
    delete node;
    --size;
}

std::string Queue::front()
{
    if(size > 0) return first->data;

    std::string emptyString;
    return emptyString;
}

bool Queue::empty()
{
    return size == 0;
}
