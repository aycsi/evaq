#pragma once

#include <cstdint>
#include <map>
#include <deque>
#include <vector>

enum class Side { Buy, Sell };
enum class OrderType { Limit, Market };

struct Order {
    uint64_t id;
    Side side;
    OrderType type;
    double px;
    uint64_t qty;
    uint64_t ts;
    int agent_id;
    
    uint64_t filled = 0;
    bool active = true;
};

struct Fill {
    uint64_t order_id;
    double px;
    uint64_t qty;
    uint64_t ts;
    int buyer_id;
    int seller_id;
};

struct PriceLevel {
    double px;
    std::deque<Order> orders;
    uint64_t total_qty = 0;
};

class OrderBook {
public:
    void add(Order o);
    std::vector<Fill> match(Order o);
    bool cancel(uint64_t order_id);
    bool empty() const;
    double best_bid() const;
    double best_ask() const;
    double mid() const;
    double spread() const;
    uint64_t bid_qty() const;
    uint64_t ask_qty() const;
    uint64_t depth(Side s, int levels) const;
    
private:
    std::map<double, PriceLevel, std::greater<double>> bids;
    std::map<double, PriceLevel> asks;
    std::map<uint64_t, std::pair<Side, double>> order_locs;
    
    PriceLevel& get_level(Side s, double px);
    void remove_order(uint64_t id, Side s, double px);
};
