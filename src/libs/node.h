#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <string>

/// Node definition.
struct Node {
    /// Holds information.
    std::string data;

    /// Pointer to the next node.
    Node* next;

    /// Default constructor.
    Node();
};

#endif // NODE_H_INCLUDED
