#pragma once

#include <cstdint>
#include <iostream>
#include <cstring>

#include "symbol.hpp"
#include "number.hpp"
#include "time.hpp"

namespace ouch {


    #pragma pack(push, 1)
    union message {
        unsigned char msg[37];
        struct {
            uint64_t timestamp;
            uint8_t messageType;
            uint64_t symbol;
            ouch::number bid = {0,0,0,0,0,0,0,0,0,0};
            ouch::number ask = {0,0,0,0,0,0,0,0,0,0};
        };

        message(const char* symbol, double bid, double ask) {
            this->timestamp = ouch::nanoseconds_since_midnight();
            this->messageType = 'U';
            this->symbol = ouch::symbol(symbol, strlen(symbol)).i64;

            ouch::toNumber(this->bid, bid);
            ouch::toNumber(this->ask, ask);
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