#include "simulator.h"

Simulator::Simulator(uint64_t seed, Logger* lg) : eng(seed), exch(lg), logger(lg) {
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
        
        uint64_t ct = eng.get_time();
        
        if (logger) {
            logger->log_book_state(exch.get_book(), ct);
        }
        
        for (auto& agent : agents) {
            agent->step(ct);
        }
        
        if (logger) {
            for (auto& agent : agents) {
                logger->log_agent_pnl(agent->get_id(), agent->get_pnl(), ct);
            }
        }
        
        current = next_step;
    }
}

double Simulator::get_agent_pnl(int agent_id) const {
    for (const auto& agent : agents) {
        if (agent->get_id() == agent_id) {
            return agent->get_pnl();
        }
    }
    return 0.0;
}
