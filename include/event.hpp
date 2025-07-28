#pragma once

#include <memory>
#include <string>

class Simulator;
class Packet;
class Node;

class Event {
public:
    double time;

    Event(double t);
    virtual ~Event() = default;
    virtual void execute(Simulator& simulator) = 0;

    bool operator>(const Event& other) const;
};

class PacketArrivalEvent : public Event {
public:
    Node* node;
    std::unique_ptr<Packet> packet;

    PacketArrivalEvent(double t, Node* n, std::unique_ptr<Packet> p);
    void execute(Simulator& simulator) override;
};

class PacketSendEvent : public Event {
public:
    Node* src;
    Node* dst;
    std::unique_ptr<Packet> packet;

    PacketSendEvent(double t, Node* s, Node* d, std::unique_ptr<Packet> p);
    void execute(Simulator& simulator) override;
};
