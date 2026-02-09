#pragma once

#include "order_book.h"
#include "agent.h"
#include <vector>
#include <memory>
#include <cstdint>

class Exchange {
public:
    void register_agent(std::shared_ptr<Agent> a);
    uint64_t submit_order(const Order& o);
    void cancel_order(uint64_t order_id);
    void process_fills(const std::vector<Fill>& fills);
    OrderBook& get_book() { return book; }
    
private:
    OrderBook book;
    std::vector<std::shared_ptr<Agent>> agents;
    uint64_t next_order_id = 1;
};
