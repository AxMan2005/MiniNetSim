#include "../include/link.hpp"
#include "../include/node.hpp"

Link::Link(Node* n1, Node* n2, double d) : node1(n1), node2(n2), delay(d) {}

Node* Link::otherEnd(Node* node) {
    return (node == node1) ? node2 : node1;
}