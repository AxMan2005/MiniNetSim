#pragma once

#include <string>
#include <vector>
#include <memory>

class PacketHeader {
public:
    virtual ~PacketHeader() = default;
};

class IPHeader : public PacketHeader {
public:
    std::string srcIP, dstIP;
    IPHeader(const std::string& src, const std::string& dst);
};

class TCPHeader : public PacketHeader {
public:
    int srcPort, dstPort;
    TCPHeader(int src, int dst);
};

class Packet {
public:
    std::vector<std::unique_ptr<PacketHeader>> headers;
    std::string payload;

    explicit Packet(const std::string& p);
    Packet(const Packet& other);  // deep copy
    void addHeader(std::unique_ptr<PacketHeader> header);
};
