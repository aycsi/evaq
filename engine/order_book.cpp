#include "order_book.h"
#include <algorithm>

void OrderBook::add(Order o) {
    if (o.type == OrderType::Market) {
        return;
    }
    
    PriceLevel& lvl = get_level(o.side, o.px);
    lvl.orders.push_back(o);
    lvl.total_qty += o.qty;
    order_locs[o.id] = {o.side, o.px};
}

std::vector<Fill> OrderBook::match(Order o) {
    std::vector<Fill> fills;
    
    auto& opp_book = (o.side == Side::Buy) ? asks : bids;
    auto opp_cmp = (o.side == Side::Buy) ? 
        [](double a, double b) { return a < b; } :
        [](double a, double b) { return a > b; };
    
    uint64_t remaining = o.qty;
    
    for (auto it = opp_book.begin(); it != opp_book.end() && remaining > 0; ) {
        double opp_px = it->first;
        
        if (o.type == OrderType::Limit && 
            ((o.side == Side::Buy && opp_px > o.px) ||
             (o.side == Side::Sell && opp_px < o.px))) {
            break;
        }
        
        PriceLevel& lvl = it->second;
        
        while (!lvl.orders.empty() && remaining > 0) {
            Order& opp = lvl.orders.front();
            uint64_t fill_qty = std::min(remaining, opp.qty - opp.filled);
            
            Fill f;
            f.order_id = opp.id;
            f.px = opp_px;
            f.qty = fill_qty;
            f.ts = o.ts;
            f.buyer_id = (o.side == Side::Buy) ? o.agent_id : opp.agent_id;
            f.seller_id = (o.side == Side::Buy) ? opp.agent_id : o.agent_id;
            fills.push_back(f);
            
            opp.filled += fill_qty;
            remaining -= fill_qty;
            lvl.total_qty -= fill_qty;
            
            if (opp.filled >= opp.qty) {
                lvl.orders.pop_front();
                order_locs.erase(opp.id);
            }
        }
        
        if (lvl.orders.empty()) {
            it = opp_book.erase(it);
        } else {
            ++it;
        }
    }
    
    if (o.type == OrderType::Limit && remaining > 0) {
        o.qty = remaining;
        add(o);
    }
    
    return fills;
}

bool OrderBook::cancel(uint64_t order_id) {
    auto it = order_locs.find(order_id);
    if (it == order_locs.end()) {
        return false;
    }
    
    Side s = it->second.first;
    double px = it->second.second;
    remove_order(order_id, s, px);
    return true;
}

double OrderBook::best_bid() const {
    return bids.empty() ? 0.0 : bids.begin()->first;
}

double OrderBook::best_ask() const {
    return asks.empty() ? 0.0 : asks.begin()->first;
}

uint64_t OrderBook::bid_qty() const {
    return bids.empty() ? 0 : bids.begin()->second.total_qty;
}

uint64_t OrderBook::ask_qty() const {
    return asks.empty() ? 0 : asks.begin()->second.total_qty;
}

PriceLevel& OrderBook::get_level(Side s, double px) {
    auto& book = (s == Side::Buy) ? bids : asks;
    return book[px];
}

void OrderBook::remove_order(uint64_t id, Side s, double px) {
    auto& book = (s == Side::Buy) ? bids : asks;
    auto it = book.find(px);
    if (it == book.end()) {
        return;
    }
    
    PriceLevel& lvl = it->second;
    auto& orders = lvl.orders;
    
    for (auto oit = orders.begin(); oit != orders.end(); ++oit) {
        if (oit->id == id) {
            lvl.total_qty -= (oit->qty - oit->filled);
            orders.erase(oit);
            break;
        }
    }
    
    if (orders.empty()) {
        book.erase(it);
    }
    
    order_locs.erase(id);
}
