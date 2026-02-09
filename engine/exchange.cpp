#include "exchange.h"

void Exchange::register_agent(std::shared_ptr<Agent> a) {
    agents.push_back(a);
}

uint64_t Exchange::submit_order(const Order& o) {
    Order order = o;
    order.id = next_order_id++;
    
    std::vector<Fill> fills = book.match(order);
    process_fills(fills);
    return order.id;
}

void Exchange::cancel_order(uint64_t order_id) {
    book.cancel(order_id);
}

void Exchange::process_fills(const std::vector<Fill>& fills) {
    for (const auto& f : fills) {
        Message msg;
        msg.type = Message::Fill;
        msg.order_id = f.order_id;
        msg.px = f.px;
        msg.qty = f.qty;
        msg.ts = f.ts;
        
        for (auto& agent : agents) {
            if (agent->get_id() == f.buyer_id || agent->get_id() == f.seller_id) {
                agent->on_message(msg);
            }
        }
    }
}
