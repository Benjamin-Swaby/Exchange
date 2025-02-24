#include <gtest/gtest.h>

#include "../include/orderbook.hpp"

#include <iostream>


class OrderFactory {
private:
    int amount;
    uint64_t ticker = 0x4141504C20202020; // 'AAPL '

    

public:

    std::vector<OrderBook::InternalOrder> buy; 
    std::vector<OrderBook::InternalOrder> sell;

    std::vector<OrderBook::InternalOrder> createOrders() {
        std::vector<OrderBook::InternalOrder> orders;

        for(int i = 0; i < amount; i++) {
            ITCH41::Add_Order_Message msg;
            msg.timestamp = i * 50;
            msg.orderReferenceNumber = i;
            msg.buySellIndicator = 'B';
            msg.shares = 100;
            msg.stock = ticker;
            msg.price = 100;

            ITCH41::Add_Order_Message msg2;
            msg2.timestamp = i * 50;
            msg2.orderReferenceNumber = amount + i;
            msg2.buySellIndicator = 'S';
            msg2.shares = 100;
            msg2.stock = ticker;
            msg2.price = 100;

            
           
            orders.push_back(OrderBook::InternalOrder(&msg));
            buy.push_back(OrderBook::InternalOrder(&msg));
            
            
            orders.push_back(OrderBook::InternalOrder(&msg2));
            sell.push_back(OrderBook::InternalOrder(&msg2));
            

        }

        return orders;
    }

    OrderFactory(int amount) {
        this->amount = amount;
    }

};




TEST(test_orderbook, new_orderbook) {

    OrderBook::StockOrderBook book(0x4141504C20202020); // 'AAPL '

    EXPECT_EQ(book.midPrice(), 0);
    EXPECT_EQ(book.volumeAtPrice(100).first, 0);
    EXPECT_EQ(book.volumeAtPrice(100).second, 0);

}

TEST(test_orderbook, add_order) {

    OrderBook::StockOrderBook book(0x4141504C20202020); // 'AAPL '


    auto order = (new OrderFactory(1))->createOrders().at(0);

    book.insert(order);

    EXPECT_EQ(book.midPrice(), 100);
    EXPECT_EQ(book.volumeAtPrice(100).first, 100);
    EXPECT_EQ(book.volumeAtPrice(100).second, 0);

}


TEST(test_orderbook, add_both_sides) {

    OrderBook::StockOrderBook book(0x4141504C20202020); // 'AAPL '

    auto of = new OrderFactory(1);
    of->createOrders();

    auto buy = of->buy.at(0);
    auto sell = of->sell.at(0);

    book.insert(buy);
    book.insert(sell); 

    std::cout << book << std::endl;

    book.match_all();

    std::cout << book << std::endl;

    EXPECT_EQ(book.midPrice(), 0); 
    EXPECT_EQ(book.volumeAtPrice(100).first, 0);
    EXPECT_EQ(book.volumeAtPrice(100).second, 0);

}


TEST(test_orderbook, match_max_profit_buy) {

    OrderBook::StockOrderBook book(0x4141504C20202020); // 'AAPL '

    auto of = new OrderFactory(1);
    of->createOrders();

    auto buy = of->buy.at(0);
    auto sell = of->sell.at(0);

    sell.price = 90;
    buy.shares = 120;
    
    book.insert(buy);
    book.insert(sell); 

    ASSERT_EQ(book.volumeAtPrice(90).second, 100);
    ASSERT_EQ(book.volumeAtPrice(90).first, 0);

    ASSERT_EQ(book.volumeAtPrice(100).first, 120);
    ASSERT_EQ(book.volumeAtPrice(100).second, 0);

    book.match_all();

    ASSERT_EQ(book.volumeAtPrice(90).second, 0);
    ASSERT_EQ(book.volumeAtPrice(90).first, 0);

    ASSERT_EQ(book.volumeAtPrice(100).first, 20);
    ASSERT_EQ(book.volumeAtPrice(100).second, 0);


}



TEST(test_orderbook, match_max_profit_sell) {

    OrderBook::StockOrderBook book(0x4141504C20202020); // 'AAPL '

    auto of = new OrderFactory(1);
    of->createOrders();

    auto buy = of->buy.at(0);
    auto sell = of->sell.at(0);

    buy.timestamp = 999; // give sell priority
    buy.price = 110; 
    buy.shares = 200;

    book.insert(sell); 
    book.insert(buy);

    
    ASSERT_EQ(book.volumeAtPrice(100).first, 0); // buy volume @ 100
    ASSERT_EQ(book.volumeAtPrice(100).second, 100); // sell volume @ 100
    

    ASSERT_EQ(book.volumeAtPrice(110).first, 200);  // buy volume @ 110
    ASSERT_EQ(book.volumeAtPrice(110).second, 0); // sell volume @ 110

    book.match_all();

    ASSERT_EQ(book.volumeAtPrice(100).first, 0);
    ASSERT_EQ(book.volumeAtPrice(100).second, 0);
    
    ASSERT_EQ(book.volumeAtPrice(110).first, 100); // buy volume at 110
    ASSERT_EQ(book.volumeAtPrice(110).second, 0);

    

}


TEST(test_orderbook, test_many_orders) {

    OrderBook::StockOrderBook book(0x4141504C20202020); // 'AAPL '

    auto of = new OrderFactory(1024);
    of->createOrders();

    for (auto o : of->buy) {
        book.insert(o);
    }

    for (auto o : of->sell) {
        book.insert(o);
    }


    std::cout << book << std::endl;

    ASSERT_EQ(book.volumeAtPrice(100).first, 102400);
    ASSERT_EQ(book.volumeAtPrice(100).second, 102400);

    book.match_all();

    std::cout << book << std::endl;

    ASSERT_EQ(book.volumeAtPrice(100).first, 0);
    ASSERT_EQ(book.volumeAtPrice(100).second, 0);

}


TEST(test_orderbook, market_depth) {

    OrderBook::StockOrderBook book(0x4141504C20202020); // 'AAPL '

    auto of = new OrderFactory(1024);
    of->createOrders();

    for (auto o : of->buy) {
        o.price = o.ID;
        book.insert(o);
    }

    for (auto o : of->sell) {
        o.price = o.ID;
        book.insert(o);
    }


    std::cout << book << std::endl;

    book.match_all();

    std::cout << book << std::endl;

    for(int i = 0; i < 1024; i++) {

        ASSERT_EQ(book.volumeAtPrice(i).first, 100);
        ASSERT_EQ(book.volumeAtPrice(i).second, 0);

        ASSERT_EQ(book.volumeAtPrice(i + 1024).first, 0);
        ASSERT_EQ(book.volumeAtPrice(i + 1024).second, 100);

    }


}