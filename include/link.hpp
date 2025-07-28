#pragma once

class Node;

class Link {
public:
    Node* node1;
    Node* node2;
    double delay;

    Link(Node* n1, Node* n2, double d);
    Node* otherEnd(Node* node);
};
