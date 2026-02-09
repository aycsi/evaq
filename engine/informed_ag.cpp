#include "informed_ag.h"
#include "order_book.h"

InformedAg::InformedAg(int id, Exchange* ex, double alpha, uint64_t qty)
    : Agent(id), exch(ex), alph(alpha), sz(qty), gen(id) {
    std::uniform_int_distribution<int> dir_dist(0, 1);
    dir = (dir_dist(gen) == 0) ? -1 : 1;
    next_time = 1000;
}

void InformedAg::on_message(const Message& m) {
}

void InformedAg::step(uint64_t ct) {
    if (ct >= next_time) {
        OrderBook& book = exch->get_book();
        double mid = (book.best_bid() + book.best_ask()) / 2.0;
        
        if (mid > 0) {
            Order o;
            o.side = (dir > 0) ? Side::Buy : Side::Sell;
            o.type = OrderType::Limit;
            o.px = mid + dir * alph;
            o.qty = sz;
            o.ts = ct;
            o.agent_id = id;
            exch->submit_order(o);
            
            next_time = ct + 5000;
            dir *= -1;
        }
    }
}
