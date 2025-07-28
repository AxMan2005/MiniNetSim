#include "../include/packet.hpp"

IPHeader::IPHeader(const std::string& src, const std::string& dst)
    : srcIP(src), dstIP(dst) {}

TCPHeader::TCPHeader(int src, int dst) : srcPort(src), dstPort(dst) {}

Packet::Packet(const std::string& p) : payload(p) {}

Packet::Packet(const Packet& other) : payload(other.payload) {
    for (const auto& header : other.headers) {
        if (auto ip = dynamic_cast<IPHeader*>(header.get())) {
            headers.push_back(std::make_unique<IPHeader>(*ip));
        } else if (auto tcp = dynamic_cast<TCPHeader*>(header.get())) {
            headers.push_back(std::make_unique<TCPHeader>(*tcp));
        }
    }
}

void Packet::addHeader(std::unique_ptr<PacketHeader> header) {
    headers.push_back(std::move(header));
}