#include "simulator.h"

Simulator::Simulator(uint64_t seed) : eng(seed) {
}

void Simulator::add_agent(std::shared_ptr<Agent> a) {
    agents.push_back(a);
    exch.register_agent(a);
}

void Simulator::run(uint64_t end_time) {
    uint64_t step_interval = 1000;
    uint64_t current = 0;
    
    while (current < end_time) {
        uint64_t next_step = current + step_interval;
        eng.run(next_step);
        
        for (auto& agent : agents) {
            agent->step(eng.get_time());
        }
        
        current = next_step;
    }
}
