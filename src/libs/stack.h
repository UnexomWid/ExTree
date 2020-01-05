#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "node.h"

struct Stack{
    Node* first;

    /// The size of the stack.
    unsigned int size;

    Stack();

    void push(std::string element);

    void pop();

    std::string top();

    bool empty();
};
/*
    Nu mai stiu de ce am pastrat portiunea de mai jos, dar vad ca functioneaza si fara ea.
    Daca nu mai avem nevoie, imi dai un mesaj si o sterg.
*/

///// Pushes the element onto the stack.
//void push(std::string, TreeStack &);
//
///// Deletes the last added element from the stack.
//void pop(TreeStack &);
//
///// Returns the top of the stack.
//std::string top(Node *);
//
///// Return whether is empty or not.
//bool empty(Node *);

#endif // STACK_H_INCLUDED
