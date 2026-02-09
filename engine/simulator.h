#pragma once

#include "event_engine.h"
#include "exchange.h"
#include "agent.h"
#include "logger.h"
#include <memory>
#include <vector>
#include <cstdint>

class Simulator {
public:
    Simulator(uint64_t seed, Logger* lg = nullptr);
    void add_agent(std::shared_ptr<Agent> a);
    void run(uint64_t end_time);
    uint64_t get_time() const { return eng.get_time(); }
    size_t num_agents() const { return agents.size(); }
    uint64_t get_volume_traded() const { return exch.get_volume_traded(); }
    double get_spread() const { return exch.get_book().spread(); }
    Exchange& get_exchange() { return exch; }
    EventEngine& get_engine() { return eng; }
    double get_agent_pnl(int agent_id) const;
    
private:
    EventEngine eng;
    Exchange exch;
    std::vector<std::shared_ptr<Agent>> agents;
    Logger* logger;
};