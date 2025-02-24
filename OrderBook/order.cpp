#include "include/order.hpp"

#include "../../ITCH/include/util.hpp"



#include<chrono>

namespace OrderBook {

    uint32_t nanoseconds_since_midnight() {
        using namespace std::chrono;

        auto now = system_clock::now();
        auto today = floor<days>(now);
        auto time_since_midnight = now - today;

        return static_cast<uint32_t>(duration_cast<nanoseconds>(time_since_midnight).count());
    }


    InternalOrder::InternalOrder(ITCH41::Add_Order_Message* msg) {

        // string representation of the stock
        ITCH41::STR_STOCK stock;
        stock.stock = msg->stock;

        this->ID = msg->orderReferenceNumber;
        this->timestamp = msg->timestamp;
        this->arrived = nanoseconds_since_midnight();
        this->delta = this->arrived - this->timestamp;
        this->price = msg->price;
        this->fillPrice = 0;
        this->filled = 0;
        this->shares = msg->shares;
        this->stock = std::string( reinterpret_cast<char*> (stock.str), 8);
        this->side = msg->buySellIndicator;
        this->MPID = std::nullopt;

    }


    InternalOrder::InternalOrder(ITCH41::Add_Order_MPID_Attribution* msg) {
        // string representation of the stock
        ITCH41::STR_STOCK stock;
        stock.stock = msg->stock;

        this->ID = msg->orderReferenceNumber;
        this->timestamp = msg->timestamp;
        this->arrived = nanoseconds_since_midnight();
        this->delta = this->arrived - this->timestamp;
        this->price = msg->price;
        this->shares = msg->shares;
        this->stock = std::string( reinterpret_cast<char*> (stock.str), 8);
        this->side = msg->buySellIndicator;
        this->MPID = msg->attribution;

    } 



    uint32_t InternalOrder::fillAgainst(InternalOrder* order) {

        if (this->side == order->side)
            return 0;

        if (this->stock != order->stock)
            return 0;
        
        uint32_t filled = 0;
        
        if (this->shares > order->shares) {
            filled =  order->shares;
            this->shares -= order->shares;
            order->shares = 0;
        }

        if (order->shares > this->shares) {
            filled = this->shares;
            order->shares -= this->shares;
            this->shares = 0;
        }

        if (order->shares == this->shares) {
            filled = this->shares;
            order->shares = 0;
            this->shares = 0;
        }

        return filled;

    }
    
}