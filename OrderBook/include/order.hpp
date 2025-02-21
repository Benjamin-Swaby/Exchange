#pragma once

#include <cstdint>
#include <string>
#include <iostream>

#include "../../ITCH/include/itch.hpp"

namespace OrderBook {

    using std::string;

    class InternalOrder {
    public: 
        uint64_t ID;
        uint32_t timestamp;
        uint32_t price;
        uint32_t shares;
        string stock;
        char side;


        InternalOrder(ITCH41::Add_Order_Message* msg);
        InternalOrder(ITCH41::Add_Order_MPID_Attribution* msg);
        InternalOrder* fillAgainst(InternalOrder* order);
        ~InternalOrder() = default;

        friend std::ostream& operator<<(std::ostream& os, const InternalOrder& order) {

            os << "ID: " << order.ID << ", "
               << "Timestamp: " << order.timestamp << ", "
               << "Price: " << order.price << ", "
               << "Shares: " << order.shares << ", "
               << "Stock: " << order.stock << ", "
               << "Side: " << order.side;

            return os;

        }

    };

}