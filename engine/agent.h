#pragma once

#include <cstdint>

struct Message {
    enum Type { Fill, CancelAck, Reject };
    Type type;
    uint64_t order_id;
    double px;
    uint64_t qty;
    uint64_t ts;
};

class Agent {
public:
    virtual ~Agent() = default;
    virtual void on_message(const Message& m) = 0;
    virtual void step(uint64_t ct) = 0;
    int get_id() const { return id; }
    double get_pnl() const { return pnl; }
    
protected:
    int id;
    double pnl = 0.0;
    Agent(int i) : id(i) {}
};
