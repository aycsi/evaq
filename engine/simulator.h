#pragma once

#include "event_engine.h"
#include "exchange.h"
#include "agent.h"
#include <memory>
#include <vector>
#include <cstdint>

class Simulator {
public:
    Simulator(uint64_t seed);
    void add_agent(std::shared_ptr<Agent> a);
    void run(uint64_t end_time);
    uint64_t get_time() const { return eng.get_time(); }
    Exchange& get_exchange() { return exch; }
    EventEngine& get_engine() { return eng; }
    double get_agent_pnl(int agent_id) const;
    
private:
    EventEngine eng;
    Exchange exch;
    std::vector<std::shared_ptr<Agent>> agents;
};