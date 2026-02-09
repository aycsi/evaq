#pragma once

#include "agent.h"
#include "exchange.h"
#include <random>

class MarketMaker : public Agent {
public:
    MarketMaker(int id, Exchange* ex, double spread, uint64_t qty);
    void on_message(const Message& m) override;
    void step(uint64_t ct) override;
    
private:
    Exchange* exch;
    double sprd;
    uint64_t sz;
    std::mt19937 gen;
    double mid = 100.0;
    uint64_t bid_id = 0;
    uint64_t ask_id = 0;
};
