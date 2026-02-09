#include "latency_model.h"

LatencyModel::LatencyModel(uint64_t seed, uint64_t base_us) 
    : gen(seed), dist(1.0), base(base_us) {
}

uint64_t LatencyModel::sample() {
    double delay = dist(gen);
    return base + static_cast<uint64_t>(delay * base);
}
