#include "../include/network.hpp"
#include "../include/node.hpp"
#include "../include/link.hpp"

Node* Network::addHost(const std::string& id) {
    nodes[id] = std::make_unique<Host>(id);
    return nodes[id].get();
}

Node* Network::addRouter(const std::string& id) {
    nodes[id] = std::make_unique<Router>(id);
    return nodes[id].get();
}

void Network::connect(const std::string& id1, const std::string& id2, double delay) {
    Node* n1 = nodes.at(id1).get();
    Node* n2 = nodes.at(id2).get();
    auto link = std::make_unique<Link>(n1, n2, delay);
    n1->addLink(link.get());
    n2->addLink(link.get());
    links.push_back(std::move(link));
}

Node* Network::getNode(const std::string& id) {
    return nodes.at(id).get();
}