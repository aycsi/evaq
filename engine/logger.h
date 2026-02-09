#pragma once

#include "order_book.h"
#include <cstdint>
#include <functional>

class Logger {
public:
    using LogFn = std::function<void(const std::string&)>;
    
    Logger(LogFn fn = nullptr);
    void log_trade(const Fill& f);
    void log_book_state(const OrderBook& book, uint64_t ts);
    void log_agent_pnl(int agent_id, double pnl, uint64_t ts);
    
private:
    LogFn log_fn;
    void write(const std::string& msg);
};
