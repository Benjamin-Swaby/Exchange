#pragma once

#include <cstdint>
#include <string>
#include <iostream>
#include <chrono>
#include <optional>

#include "../../ITCH/include/itch.hpp"

namespace OrderBook {

    uint32_t nanoseconds_since_midnight();

    using std::string;

    class InternalOrder {
    public: 
        uint64_t ID;
        uint32_t timestamp;
        uint32_t arrived;
        uint32_t delta;
        uint32_t price;

        mutable uint32_t filled;
        mutable uint32_t fillPrice;
        mutable uint32_t shares;

        string stock;
        std::optional<uint64_t> MPID;
        char side;


        InternalOrder(ITCH41::Add_Order_Message* msg);
        InternalOrder(ITCH41::Add_Order_MPID_Attribution* msg);
        uint32_t fillAgainst(InternalOrder* order);
        ~InternalOrder() = default;
        InternalOrder() = default;


        // Priority Given to Lower Timestamps (they arrived first)
        friend bool operator <(const InternalOrder& lhs, const InternalOrder& rhs) {
            return lhs.timestamp < rhs.timestamp; // higher timestamp is newer 
        }

        friend bool operator >(const InternalOrder& lhs, const InternalOrder& rhs) {
            return lhs.timestamp > rhs.timestamp; // lower timestamp is older 
        }

        friend bool operator ==(const InternalOrder& lhs, const InternalOrder& rhs) {
            return lhs.timestamp == rhs.timestamp;
        }


        friend std::ostream& operator<<(std::ostream& os, const InternalOrder& order) {
            os << "ID: " << order.ID << ", "
               << "Timestamp: " << order.timestamp << ", "
               << "Arrived: " << order.arrived << ", "
               << "Delta: " << order.delta << ", "
               << "Price: " << order.price << ", "
               << "Shares: " << order.shares << ", "
               << "Stock: " << order.stock << ", "
               << "MPID: " << (order.MPID ? std::to_string(order.MPID.value()) : "N/A") << ", "
               << "Side: " << order.side;
            return os;
        }

    };

}