#pragma once

#include <cstdint>
#include <queue>
#include <functional>

struct Event {
    uint64_t ts;
    std::function<void()> fn;
    
    bool operator>(const Event& o) const {
        return ts > o.ts;
    }
};

class EventEngine {
public:
    void schedule(Event e);
    void run(uint64_t end_time);
    
private:
    std::priority_queue<Event, std::vector<Event>, std::greater<Event>> pq;
    uint64_t ct = 0;
};
