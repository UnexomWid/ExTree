#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <string>

/// Represents a simple linked list node that stores a string.
struct Node {
    /// The string stored in this node.
    std::string data;

    /// The pointer to the next node.
    Node* next;

    /// Default constructor.
    Node();
};

#endif // NODE_H_INCLUDED
