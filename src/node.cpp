#include "../include/node.hpp"
#include "../include/link.hpp"
#include "../include/packet.hpp"
#include "../include/simulator.hpp"
#include "../include/event.hpp"

Node::Node(std::string id_) : id(std::move(id_)) {}

void Node::addLink(Link* link) {
    links.push_back(link);
}

void Host::receive(Packet* packet, Simulator& simulator) {
    simulator.log("Host " + id + " received packet with payload: " + packet->payload);
}

void Router::receive(Packet* packet, Simulator& simulator) {
    simulator.log("Router " + id + " received packet, forwarding...");

    std::string destinationIP;
    // Find the IP header to get the destination IP
    for (const auto& header : packet->headers) {
        if (auto ipHeader = dynamic_cast<IPHeader*>(header.get())) {
            destinationIP = ipHeader->dstIP;
            break;
        }
    }

    if (destinationIP.empty()) {
        simulator.log("Router " + id + ": No IP header found, dropping packet.");
        return;
    }

    Link* forwardLink = nullptr;
    Node* nextHop = nullptr;

    for (Link* link : links) {
        Node* otherEndNode = link->otherEnd(this);
        if (otherEndNode->id == destinationIP) {
            forwardLink = link;
            nextHop = otherEndNode;
            break;
        }
    }

    if (forwardLink && nextHop) {
        simulator.schedule(std::make_unique<PacketArrivalEvent>(
            simulator.currentTime + forwardLink->delay,
            nextHop,
            std::make_unique<Packet>(*packet) // Make a copy for the new event
        ));
    } else {
        simulator.log("Router " + id + ": No route found for destination " + destinationIP + ", dropping packet.");
    }
}