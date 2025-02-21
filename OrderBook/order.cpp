#include "include/order.hpp"

#include "../../ITCH/include/util.hpp"

namespace OrderBook {

    InternalOrder::InternalOrder(ITCH41::Add_Order_Message* msg) {

        // string representation of the stock
        ITCH41::STR_STOCK stock;
        stock.stock = msg->stock;

        this->ID = msg->orderReferenceNumber;
        this->timestamp = msg->timestamp;
        this->price = msg->price;
        this->shares = msg->shares;
        this->stock = std::string( reinterpret_cast<char*> (stock.str), 8);
        this->side = msg->buySellIndicator;

    }
    
}