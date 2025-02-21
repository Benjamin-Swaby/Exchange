#pragma once

#include <cstdint>
#include <iostream>

#include "symbol.hpp"
#include "number.hpp"
#include "time.hpp"

namespace outch {


    #pragma pack(push, 1)
    union message {
        unsigned char msg[37];
        struct {
            uint64_t timestamp;
            uint8_t messageType;
            uint64_t symbol;
            outch::number bid = {0,0,0,0,0,0,0,0,0,0};
            outch::number ask = {0,0,0,0,0,0,0,0,0,0};
        };

        message(const char* symbol, float bid, float ask) {
            this->timestamp = outch::nanoseconds_since_midnight();
            this->messageType = 'U';
            this->symbol = outch::symbol(symbol).i64;

            outch::toNumber(this->bid, bid);
            outch::toNumber(this->ask, ask);
        }
    };
    #pragma pack(pop)


    std::ostream& operator<<(std::ostream& os, const message& msg) {
        os << "Timestamp: " << msg.timestamp << ", "
           << "MessageType: " << static_cast<char>(msg.messageType) << ", "
           << "Symbol: " << msg.symbol << ", "
           << "Bid: " << msg.bid << ", "
           << "Ask: " << msg.ask;
        return os;
    }
    

}