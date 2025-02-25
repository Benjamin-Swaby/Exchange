#include <gtest/gtest.h>
#include "../include/order.hpp"



TEST(test_order, from_ITCH41_Add_Order_Message) {

    unsigned char msg[] = {
        'A', // messageType Add Order
        0x32, 0x09, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, // 67890 // 4 byte timestamp
        0x40, 0xE2, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, // 8 Byte reference number 123456
        'B', // Buy sell indicator 
        0x32, 0x09, 0x01, 0x00, // 67890 // 4 byte number of shares
        0x41, 0x41, 0x50, 0x4C, 0x20, 0x20, 0x20, 0x20, // 8 Byte AAPL stock,
        0x32, 0x09, 0x01, 0x00, // 67890 // 4 byte price.
    };

    OrderBook::InternalOrder order( (ITCH41::Add_Order_Message*) msg);

    EXPECT_EQ(order.ID, 123456);
    EXPECT_EQ(order.timestamp, 67890);
    EXPECT_EQ(order.price, 67890);
    EXPECT_EQ(order.shares, 67890);
    EXPECT_EQ(order.stock, "AAPL    ");
    EXPECT_EQ(order.side, 'B');
    EXPECT_FALSE(order.MPID.has_value());

}



TEST(test_order, from_ITCH41_Add_Order_MPID_Attribution) {

    unsigned char msg[] = {
        'F', // messageType Add Order
        0x32, 0x09, 0x01, 0x00,0x00, 0x00, 0x00, 0x00, // 67890 // 4 byte timestamp
        0x40, 0xE2, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, // 8 Byte reference number 123456
        'B', // Buy sell indicator 
        0x32, 0x09, 0x01, 0x00, // 67890 // 4 byte number of shares
        0x41, 0x41, 0x50, 0x4C, 0x20, 0x20, 0x20, 0x20, // 8 Byte AAPL stock,
        0x32, 0x09, 0x01, 0x00, // 67890 // 4 byte price.
        0x32, 0x09, 0x01, 0x00, // 67890 // 4 byte attribution
    };

    OrderBook::InternalOrder order( (ITCH41::Add_Order_MPID_Attribution*) msg);

    EXPECT_EQ(order.ID, 123456);
    EXPECT_EQ(order.timestamp, 67890);
    EXPECT_EQ(order.price, 67890);
    EXPECT_EQ(order.shares, 67890);
    EXPECT_EQ(order.stock, "AAPL    ");
    EXPECT_EQ(order.side, 'B');
    EXPECT_EQ(order.MPID.value(), 67890);

}



TEST(test_order, fill_order_eq_vol) {

    ITCH41::Add_Order_Message msg1;
    msg1.timestamp = 67890;
    msg1.orderReferenceNumber = 123456;
    msg1.buySellIndicator = 'B';
    msg1.shares = 100;
    msg1.stock = 0x4141504C20202020; // 'AAPL '
    msg1.price = 100;

    auto order1 = new OrderBook::InternalOrder(&msg1);

    ITCH41::Add_Order_Message msg2;
    msg2.timestamp = 67890;
    msg2.orderReferenceNumber = 123457;
    msg2.buySellIndicator = 'S';
    msg2.shares = 100;
    msg2.stock = 0x4141504C20202020; // 'AAPL '
    msg2.price = 90;

    auto order2 = new OrderBook::InternalOrder(&msg2);

    auto filled = order1->fillAgainst(order2);
    EXPECT_EQ(order1->shares, 0);
    EXPECT_EQ(order2->shares, 0);
    EXPECT_EQ(filled, 100); // All shares were filled

    // RESET THE ORDERS
    order1 = new OrderBook::InternalOrder(&msg1);
    order2 = new OrderBook::InternalOrder(&msg2);

    filled = order2->fillAgainst(order1);
    EXPECT_EQ(order1->shares, 0);
    EXPECT_EQ(order2->shares, 0);
    EXPECT_EQ(filled, 100); // All shares were filled

}


TEST(test_order, fill_order_neq_vol) {

    ITCH41::Add_Order_Message msg1;
    msg1.timestamp = 67890;
    msg1.orderReferenceNumber = 123456;
    msg1.buySellIndicator = 'B';
    msg1.shares = 120;              // Increase in volume : 120B vs 100S
    msg1.stock = 0x4141504C20202020; // 'AAPL '
    msg1.price = 100;

    auto order1 = new OrderBook::InternalOrder(&msg1);

    ITCH41::Add_Order_Message msg2;
    msg2.timestamp = 67890;
    msg2.orderReferenceNumber = 123457;
    msg2.buySellIndicator = 'S';
    msg2.shares = 100;
    msg2.stock = 0x4141504C20202020; // 'AAPL '
    msg2.price = 90;

    auto order2 = new OrderBook::InternalOrder(&msg2);


    auto filled = order1->fillAgainst(order2);
    EXPECT_EQ(order1->shares, 20);
    EXPECT_EQ(order2->shares, 0);
    EXPECT_EQ(filled, 100); // 100 shares should be filled

    // reset the orders
    order1 = new OrderBook::InternalOrder(&msg1);
    order2 = new OrderBook::InternalOrder(&msg2);

    filled = order2->fillAgainst(order1);
    EXPECT_EQ(order1->shares, 20);
    EXPECT_EQ(order2->shares, 0);
    EXPECT_EQ(filled, 100); // 100 shares should be filled

}


TEST(test_order, fill_order_same_side) {

    ITCH41::Add_Order_Message msg1;
    msg1.timestamp = 67890;
    msg1.orderReferenceNumber = 123456;
    msg1.buySellIndicator = 'B';
    msg1.shares = 100;           
    msg1.stock = 0x4141504C20202020; // 'AAPL '
    msg1.price = 100;

    auto order1 = new OrderBook::InternalOrder(&msg1);

    ITCH41::Add_Order_Message msg2;
    msg2.timestamp = 67890;
    msg2.orderReferenceNumber = 123457;
    msg2.buySellIndicator = 'B';            // Both orders are buy orders
    msg2.shares = 100;
    msg2.stock = 0x4141504C20202020; // 'AAPL '
    msg2.price = 90;

    auto order2 = new OrderBook::InternalOrder(&msg2);


    auto filled = order1->fillAgainst(order2);
    ASSERT_EQ(order1->shares, 100);
    ASSERT_EQ(order2->shares, 100);
    ASSERT_EQ(filled, 0); // No shares should be filled

}


TEST(test_order, fill_order_different_stock) {

    ITCH41::Add_Order_Message msg1;
    msg1.timestamp = 67890;
    msg1.orderReferenceNumber = 123456;
    msg1.buySellIndicator = 'B';
    msg1.shares = 100;           
    msg1.stock = 0x4141504C20202020; // 'AAPL '
    msg1.price = 100;

    auto order1 = new OrderBook::InternalOrder(&msg1);

    ITCH41::Add_Order_Message msg2;
    msg2.timestamp = 67890;
    msg2.orderReferenceNumber = 123457;
    msg2.buySellIndicator = 'S';            // Both orders are buy orders
    msg2.shares = 100;
    msg2.stock = 0x4E56444120202020; // 'NVDA    '
    msg2.price = 90;

    auto order2 = new OrderBook::InternalOrder(&msg2);

    auto filled = order1->fillAgainst(order2);
    ASSERT_EQ(order1->shares, 100);
    ASSERT_EQ(order2->shares, 100);
    ASSERT_EQ(filled, 0); // No shares should be filled

}
