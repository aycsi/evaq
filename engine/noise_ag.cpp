#include "noise_ag.h"
#include "order_book.h"
#include <algorithm>

NoiseAg::NoiseAg(int id, Exchange* ex, double lambda, uint64_t qty)
    : Agent(id), exch(ex), lam(lambda), sz(qty), gen(id), exp_dist(lambda) {
    next_time = static_cast<uint64_t>(exp_dist(gen));
}

void NoiseAg::on_message(const Message& m) {
}

void NoiseAg::step(uint64_t ct) {
    if (ct >= next_time) {
        OrderBook& book = exch->get_book();
        double bb = book.best_bid();
        double ba = book.best_ask();
        
        if (bb > 0 && ba > 0) {
            std::uniform_int_distribution<int> side_dist(0, 1);
            Side s = (side_dist(gen) == 0) ? Side::Buy : Side::Sell;
            
            Order o;
            o.side = s;
            o.type = OrderType::Market;
            o.qty = sz;
            o.ts = ct;
            o.agent_id = id;
            exch->submit_order(o);
        }
        
        next_time = ct + static_cast<uint64_t>(exp_dist(gen));
    }
}
