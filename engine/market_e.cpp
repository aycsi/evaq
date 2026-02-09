#include "market_e.h"
#include "order_book.h"

MarketE::MarketE(int id, Exchange* ex, double spread, uint64_t qty)
    : Agent(id), exch(ex), sprd(spread), sz(qty), gen(id) {
}

void MarketE::on_message(const Message& m) {
    if (m.type == Message::Fill) {
        if (m.order_id == bid_id) {
            pnl -= m.px * m.qty;
            bid_id = 0;
        } else if (m.order_id == ask_id) {
            pnl += m.px * m.qty;
            ask_id = 0;
        }
    }
}

void MarketE::step(uint64_t ct) {
    OrderBook& book = exch->get_book();
    double m = book.mid();
    if (m > 0) {
        mid = m;
    }
    
    if (bid_id == 0 && ask_id == 0) {
        Order bid;
        bid.side = Side::Buy;
        bid.type = OrderType::Limit;
        bid.px = mid - sprd / 2.0;
        bid.qty = sz;
        bid.ts = ct;
        bid.agent_id = id;
        bid_id = exch->submit_order(bid);
        
        Order ask;
        ask.side = Side::Sell;
        ask.type = OrderType::Limit;
        ask.px = mid + sprd / 2.0;
        ask.qty = sz;
        ask.ts = ct;
        ask.agent_id = id;
        ask_id = exch->submit_order(ask);
    }
}
