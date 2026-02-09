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
    EventEngine(uint64_t seed = 0);
    void schedule(Event e);
    void run(uint64_t end_time);
    uint64_t get_time() const { return ct; }
    
private:
    std::priority_queue<Event, std::vector<Event>, std::greater<Event>> pq;
    uint64_t ct = 0;
};
