#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "node.hpp"
#include "link.hpp"

class Network {
public:
    std::map<std::string, std::unique_ptr<Node>> nodes;
    std::vector<std::unique_ptr<Link>> links;

    Node* addHost(const std::string& id);
    Node* addRouter(const std::string& id);
    void connect(const std::string& id1, const std::string& id2, double delay);
    Node* getNode(const std::string& id);
};
