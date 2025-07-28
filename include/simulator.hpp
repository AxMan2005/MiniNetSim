#pragma once

#include <queue>
#include <vector>
#include <memory>
#include <string>

class Event;

class Simulator {
    struct EventComparator {
        bool operator()(const std::unique_ptr<Event>& a, const std::unique_ptr<Event>& b);
    };

public:
    std::priority_queue<std::unique_ptr<Event>, std::vector<std::unique_ptr<Event>>, EventComparator> eventQueue;
    double currentTime = 0.0;

    void schedule(std::unique_ptr<Event> event);
    void start();
    void log(const std::string& msg);
};
