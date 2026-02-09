#include "informed_ag.h"
#include "order_book.h"

InformedAg::InformedAg(int id, Exchange* ex, double alpha, uint64_t qty)
    : Agent(id), exch(ex), alph(alpha), sz(qty), gen(id) {
    std::uniform_int_distribution<int> dir_dist(0, 1);
    dir = (dir_dist(gen) == 0) ? -1 : 1;
    next_time = 1000;
}

void InformedAg::on_message(const Message& m) {
    if (m.type == Message::Fill && m.order_id == pending_order) {
        if (pending_side == Side::Buy) {
            pnl -= m.px * m.qty;
        } else {
            pnl += m.px * m.qty;
        }
        pending_order = 0;
    }
}

void InformedAg::step(uint64_t ct) {
    if (ct >= next_time) {
        OrderBook& book = exch->get_book();
        double m = book.mid();
        
        if (m > 0) {
            Order o;
            o.side = (dir > 0) ? Side::Buy : Side::Sell;
            o.type = OrderType::Limit;
            o.px = m + dir * alph;
            o.qty = sz;
            o.ts = ct;
            o.agent_id = id;
            pending_order = exch->submit_order(o);
            pending_side = o.side;
            
            next_time = ct + 5000;
            dir *= -1;
        }
    }
}
