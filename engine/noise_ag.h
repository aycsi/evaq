#pragma once

#include "agent.h"
#include "exchange.h"
#include <random>

class NoiseAg : public Agent {
public:
    NoiseAg(int id, Exchange* ex, double lambda, uint64_t qty);
    void on_message(const Message& m) override;
    void step(uint64_t ct) override;
    
private:
    Exchange* exch;
    double lam;
    uint64_t sz;
    std::mt19937 gen;
    std::exponential_distribution<double> exp_dist;
    uint64_t next_time = 0;
};
