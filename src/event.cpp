#include "../include/event.hpp"
#include "../include/simulator.hpp"
#include "../include/node.hpp"
#include "../include/packet.hpp"
#include "../include/link.hpp"

Event::Event(double t) : time(t) {}

bool Event::operator>(const Event& other) const {
    return time > other.time;
}

PacketArrivalEvent::PacketArrivalEvent(double t, Node* n, std::unique_ptr<Packet> p)
    : Event(t), node(n), packet(std::move(p)) {}

void PacketArrivalEvent::execute(Simulator& simulator) {
    node->receive(packet.get(), simulator);
}

PacketSendEvent::PacketSendEvent(double t, Node* s, Node* d, std::unique_ptr<Packet> p)
    : Event(t), src(s), dst(d), packet(std::move(p)) {}

void PacketSendEvent::execute(Simulator& simulator) {
    simulator.log("Packet sent from " + src->id + " to " + dst->id);

    // Find the link connecting src and dst
    Link* connectingLink = nullptr;
    for (Link* link : src->links) {
        if (link->otherEnd(src) == dst) {
            connectingLink = link;
            break;
        }
    }

    if (connectingLink) {
        // Schedule the PacketArrivalEvent at the destination
        // after the link's delay has passed.
        simulator.schedule(std::make_unique<PacketArrivalEvent>(
            simulator.currentTime + connectingLink->delay,
            dst,
            std::move(packet) // Move ownership of the packet to the new event
        ));
    } else {
        simulator.log("Error: No direct link found between " + src->id + " and " + dst->id + ". Packet dropped.");
        // The packet ownership is released here if no link is found.
    }
}