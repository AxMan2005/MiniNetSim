#include "include/network.hpp"
#include "include/simulator.hpp"
#include "include/packet.hpp"
#include "include/event.hpp"
#include <memory>
#include <iostream>

int main() {
    Network network;
    Simulator simulator;

    // Create nodes: 3 hosts and 1 central router
    auto* hostA = network.addHost("A");
    auto* hostB = network.addHost("B");
    auto* hostC = network.addHost("C");
    auto* routerR = network.addRouter("R");

    // Connect nodes to the central router with different delays
    // H --- R --- H
    //       |
    //       H
    network.connect("A", "R", 1.0); // Link A-R with 1.0 delay
    network.connect("B", "R", 1.5); // Link B-R with 1.5 delay
    network.connect("C", "R", 2.0); // Link C-R with 2.0 delay

    // --- Packet 1: From A to B ---
    auto packet1 = std::make_unique<Packet>("Hello from A to B!");
    packet1->addHeader(std::make_unique<IPHeader>("A", "B")); // Source A, Destination B
    packet1->addHeader(std::make_unique<TCPHeader>(1000, 80)); // SrcPort 1000, DstPort 80
    simulator.schedule(std::make_unique<PacketSendEvent>(0.0, hostA, routerR, std::move(packet1))); // Scheduled at t=0.0

    // --- Packet 2: From B to A ---
    auto packet2 = std::make_unique<Packet>("Hello from B to A!");
    packet2->addHeader(std::make_unique<IPHeader>("B", "A")); // Source B, Destination A
    packet2->addHeader(std::make_unique<TCPHeader>(2000, 21)); // SrcPort 2000, DstPort 21
    simulator.schedule(std::make_unique<PacketSendEvent>(0.1, hostB, routerR, std::move(packet2))); // Scheduled slightly after at t=0.1

    // --- Packet 3: From A to C ---
    auto packet3 = std::make_unique<Packet>("Hello from A to C!");
    packet3->addHeader(std::make_unique<IPHeader>("A", "C")); // Source A, Destination C
    packet3->addHeader(std::make_unique<TCPHeader>(1000, 25)); // SrcPort 1000, DstPort 25
    simulator.schedule(std::make_unique<PacketSendEvent>(0.2, hostA, routerR, std::move(packet3))); // Scheduled slightly after at t=0.2

    std::cout << "Starting simulation..." << std::endl;
    simulator.start();
    std::cout << "Simulation finished." << std::endl;

    return 0;
}