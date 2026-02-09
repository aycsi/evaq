#pragma once

#include "agent.h"
#include "exchange.h"
#include "order_book.h"
#include <random>

class InformedAg : public Agent {
public:
    InformedAg(int id, Exchange* ex, double alpha, uint64_t qty);
    void on_message(const Message& m) override;
    void step(uint64_t ct) override;
    
private:
    Exchange* exch;
    double alph;
    uint64_t sz;
    std::mt19937 gen;
    int dir = 0;
    uint64_t next_time = 0;
    uint64_t pending_order = 0;
    Side pending_side = Side::Buy;
};
