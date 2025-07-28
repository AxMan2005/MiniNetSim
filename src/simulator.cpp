#include "../include/simulator.hpp"
#include "../include/event.hpp"
#include <iostream>
#include <chrono>
#include <thread>

bool Simulator::EventComparator::operator()(const std::unique_ptr<Event>& a, const std::unique_ptr<Event>& b) {
    return *a > *b;
}

void Simulator::schedule(std::unique_ptr<Event> event) {
    eventQueue.push(std::move(event));
}

void Simulator::start() {
    double lastTime = 0.0;
    double timeScale = 1000.0; // Sim time to ms scaling

    while (!eventQueue.empty()) {
        std::unique_ptr<Event> event = std::move(const_cast<std::unique_ptr<Event>&>(eventQueue.top()));
        eventQueue.pop();

        double delay = (event->time - lastTime) * timeScale;
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(delay)));
        lastTime = event->time;
        currentTime = event->time;
        event->execute(*this);
    }
}

void Simulator::log(const std::string& msg) {
    std::cout << "[t=" << currentTime << "] " << msg << std::endl;
}