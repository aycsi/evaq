#include "simulator.h"
#include "market_e.h"
#include "noise_ag.h"
#include "logger.h"
#include <memory>

int main() {
    Logger logger;
    Simulator sim(42, &logger);
    
    auto mm = std::make_shared<MarketE>(1, &sim.get_exchange(), 0.01, 100);
    sim.add_agent(mm);
    
    auto nt = std::make_shared<NoiseAg>(2, &sim.get_exchange(), 0.001, 50);
    sim.add_agent(nt);
    
    sim.run(100000);
    
    return 0;
}
