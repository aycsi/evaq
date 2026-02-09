#include "event_engine.h"

EventEngine::EventEngine(uint64_t seed) : ct(0) {
}

void EventEngine::schedule(Event e) {
    pq.push(e);
}

void EventEngine::run(uint64_t end_time) {
    while (!pq.empty() && pq.top().ts <= end_time) {
        ct = pq.top().ts;
        pq.top().fn();
        pq.pop();
    }
}
