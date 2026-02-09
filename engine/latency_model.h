#pragma once

#include <cstdint>
#include <random>

class LatencyModel {
public:
    LatencyModel(uint64_t seed, uint64_t base_us);
    uint64_t sample();
    
private:
    std::mt19937 gen;
    std::exponential_distribution<double> dist;
    uint64_t base;
};
