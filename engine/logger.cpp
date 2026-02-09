#include "logger.h"
#include <sstream>
#include <iostream>
#include <string>

Logger::Logger(LogFn fn) : log_fn(fn) {
    if (!log_fn) {
        log_fn = [](const std::string& msg) {
            std::cout << msg << std::endl;
        };
    }
}

void Logger::log_trade(const Fill& f) {
    std::ostringstream oss;
    oss << "TRADE," << f.ts << "," << f.order_id << "," 
        << f.px << "," << f.qty << "," << f.buyer_id << "," << f.seller_id;
    write(oss.str());
}

void Logger::log_book_state(const OrderBook& book, uint64_t ts) {
    std::ostringstream oss;
    oss << "BOOK," << ts << "," << book.best_bid() << "," 
        << book.best_ask() << "," << book.spread() << "," 
        << book.bid_qty() << "," << book.ask_qty();
    write(oss.str());
}

void Logger::log_agent_pnl(int agent_id, double pnl, uint64_t ts) {
    std::ostringstream oss;
    oss << "PNL," << ts << "," << agent_id << "," << pnl;
    write(oss.str());
}

void Logger::write(const std::string& msg) {
    log_fn(msg);
}
