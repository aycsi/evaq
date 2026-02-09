#pragma once

#include "order_book.h"
#include "agent.h"
#include "logger.h"
#include <vector>
#include <memory>
#include <cstdint>

class Exchange {
public:
    Exchange(Logger* lg = nullptr) : logger(lg) {}
    void register_agent(std::shared_ptr<Agent> a);
    uint64_t submit_order(const Order& o);
    void cancel_order(uint64_t order_id);
    void process_fills(const std::vector<Fill>& fills);
    uint64_t get_order_count() const { return next_order_id - 1; }
    uint64_t get_volume_traded() const { return volume_traded; }
    OrderBook& get_book() { return book; }
    
private:
    OrderBook book;
    std::vector<std::shared_ptr<Agent>> agents;
    uint64_t next_order_id = 1;
    uint64_t volume_traded = 0;
    Logger* logger;
};
