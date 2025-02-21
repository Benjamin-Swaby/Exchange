#include <gtest/gtest.h>
#include "../include/order.hpp"



TEST(test_order, from_ITCH41_Add_Order_Message) {

    unsigned char msg[] = {
        'A', // messageType Add Order
        0x32, 0x09, 0x01, 0x00, // 67890 // 4 byte timestamp
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

}
