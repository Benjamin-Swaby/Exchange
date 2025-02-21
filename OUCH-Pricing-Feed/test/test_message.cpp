#include <gtest/gtest.h>

#include "../include/message.hpp"


bool compare_number(const unsigned char* a, const unsigned char* b) {
    for(int i = 0; i < 10; i++) {
        if(a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

TEST(test_message, validMessage) {

    auto msg = ouch::message("AAPL", 100.0, 101.0);

    ASSERT_EQ(msg.symbol, 1280328001);
    const unsigned char expectedBid[10] = {0,0,0,1,0,0,0,0,0,0};
    const unsigned char expectedAsk[10] = {0,0,0,1,0,1,0,0,0,0};

    ASSERT_TRUE( compare_number(msg.bid, expectedBid) );
    ASSERT_TRUE( compare_number(msg.ask, expectedAsk) );
    ASSERT_EQ(msg.messageType,  'U');
    
}


TEST(test_message, tickerTooBig) {

    auto msg = ouch::message("AAPL12345", 100.0, 101.0);

    ASSERT_EQ(msg.symbol, 3761405301099610433); // jest take AAPL1234
    const unsigned char expectedBid[10] = {0,0,0,1,0,0,0,0,0,0};
    const unsigned char expectedAsk[10] = {0,0,0,1,0,1,0,0,0,0};

    ASSERT_TRUE( compare_number(msg.bid, expectedBid) );
    ASSERT_TRUE( compare_number(msg.ask, expectedAsk) );
    ASSERT_EQ(msg.messageType,  'U');

}


TEST(test_message, toByteArray) {

    auto msg = ouch::message("AAPL", 100.0, 101.0);

    msg.timestamp = 0; // override timestamp for testing


    unsigned char Expected[37] = {
        // Offset 0x00000000 to 0x00000024
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x41, 0x41, 0x50,
        0x4C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x00
    };

    ASSERT_TRUE( compare_number(msg.msg, Expected) );
        

}


TEST(test_message, fromByteArray) {


    unsigned char input[37] = {
        // Offset 0x00000000 to 0x00000024
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x41, 0x41, 0x50,
        0x4C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x00
    };

    ouch::message* msg = (ouch::message*)input; //cast byte array to message!

    ASSERT_EQ(msg->symbol, 1280328001);
    ASSERT_EQ(msg->timestamp, 0);
    ASSERT_EQ(msg->messageType, 'U');

    unsigned char bid[10] = {0,0,0,1,0,0,0,0,0,0};
    unsigned char ask[10] = {0,0,0,1,0,1,0,0,0,0};

    ASSERT_TRUE( compare_number(msg->bid,  bid));
    ASSERT_TRUE( compare_number(msg->ask, ask));
    

}