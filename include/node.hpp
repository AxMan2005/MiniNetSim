#pragma once

#include <string>
#include <vector>

class Link;
class Packet;
class Simulator;

class Node {
public:
    std::string id;
    std::vector<Link*> links;

    explicit Node(std::string id_);
    virtual ~Node() = default;
    void addLink(Link* link);
    virtual void receive(Packet* packet, Simulator& simulator) = 0;
};

class Host : public Node {
public:
    using Node::Node;
    void receive(Packet* packet, Simulator& simulator) override;
};

class Router : public Node {
public:
    using Node::Node;
    void receive(Packet* packet, Simulator& simulator) override;
};
