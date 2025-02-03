#include<gtest/gtest.h>

#include "../include/itch.hpp"
#include "../include/handlerInterface.hpp"

using namespace ITCH41;

class test_handler : public ITCH41::ITCH_Handler {
public:
    int flag = 0;
    int flags[10] = {0,0,0,0,0,0,0,0,0,0};

    void handle(ITCH41::System_Event_Message* msg, int socket) override {
        flags[6] = 1;
        flags[0] = (msg->messageType == 'S');
        flags[1] = (msg->timestamp == 0);
        flags[2] = (msg->eventCode == 'O');
        flag = flags[0] && flags[1] && flags[2];
    }

    void handle(Stock_Directory* m, int socket) {
        flags[6] = 1;
        flags[0] = (m->messageType == 'R');
        flags[1] = (m->timestamp == 67890);
        flags[2] = (m->marketCategory == 'Q');
        flags[3] = (m->financialStatusIndicator == 'N');
        flags[4] = (m->roundLotSize == 100);
        flags[5] = (m->roundLotsOnly == 'Y');
        flag = flags[0] && flags[1] && flags[2] && flags[3] && flags[4] && flags[5];
    }

    void handle(Stock_Trading_Action* m, int socket) {
        flags[6] = 1;
        flags[0] = (m->messageType == 'H');
        flags[1] = (m->timestamp == 67890);
        flags[2] = (m->reserved == 0);
        flags[3] = (m->tradingState == 'T');
    }

    void handle(Reg_SHO_Restriction* m, int socket) {
        flags[6] = 1;
        flags[0] = (m->messageType == 'Y');
        flags[1] = (m->timestamp == 67890);
        flags[2] = (m->regSHOAction == '1');
    }

    void handle(Market_Participant_Position* m, int socket) {
        flags[6] = 1;
        flags[0] = (m->messageType == 'L');
        flags[1] = (m->timestamp == 67890);
        flags[2] = (m->MPID == 67890);
        flags[3] = (m->primaryMarketMaker == 'Y');
        flags[4] = (m->marketMakerMode == 'N');
        flags[5] = (m->marketParticipantState == 'A');
    }

    void handle(Add_Order_Message* m, int socket) {
        flags[6] = 1;
        flags[0] = (m->messageType == 'A');
        flags[1] = (m->timestamp == 67890);
        flags[2] = (m->buySellIndicator == 'B');
        flags[3] = (m->shares == 67890);
        flags[4] = (m->price == 67890);
    }

    void handle(Add_Order_MPID_Attribution* m, int socket) {return;}
    void handle(Order_Executed_Message* m, int socket) {return;}
    void handle(Order_Executed_With_Price_Message* m, int socket) {return;}
    void handle(Order_Cancel_Message* m, int socket) {return;}
    void handle(Order_Delete_Message* m, int socket) {return;}
    void handle(Order_Replace_Message* m, int socket) {return;}
    void handle(Trade_Message* m, int socket) {return;}
    void handle(Cross_Trade_Message* m, int socket) {return;}
    void handle(Broken_Trade_Message* m, int socket) {return;}
    void handle(NOII_Message* m, int socket) {return;}
    void handle(RPII_Message* m, int socket) {return;}
};


TEST(handler, system_event_message) {

    unsigned char buffer[] = {0x53, 0x00, 0x00, 0x00, 0x00, 0x4F};
    auto th = new test_handler;

    // calling action on the buffer should handle this as a System_Event_Message
    // This if done correctly will set the flag attribute in th to 1
    th->action(buffer, 6, 0);

    EXPECT_EQ(th->flag, 1);

}


TEST(handler, stock_directory) {   
    // Stock Directory Message
    // Message Type: 'R' (Stock Directory)
    // Timestamp: 67890
    // Stock: "AAPL    "
    // Market Category: 'Q'
    // Financial Status Indicator: 'N'
    // Round Lot Size: 100
    // Round Lots Only: 'Y'
    unsigned char buffer[] = {
        0x52, // 'R' 1 byte messageType
        0x32, 0x09, 0x01, 0x00, // 67890 // 4 byte timestamp
        0x41, 0x41, 0x50, 0x4C, 0x20, 0x20, 0x20, 0x20, // 8 byte stock 'AAPL    '
        0x51, // Market Category 1 byte 'Q'
        0x4E, // Financial Status Indicator: 'N' 1 Byte
        0x64, 0x00, 0x00, 0x00, // 100 4 byte round lot size
        0x59 // 1 byte roundLotsOnly 'Y'
    };

    
    auto th = new test_handler;

    // calling action on the buffer should handle this as a Stock_Directory_Message
    // This if done correctly will set the flag attribute in th to 1
    th->action(buffer, 20, 0);


    EXPECT_EQ(th->flags[0], 1);
    EXPECT_EQ(th->flags[1], 1);
    EXPECT_EQ(th->flags[2], 1);
    EXPECT_EQ(th->flags[3], 1);
    EXPECT_EQ(th->flags[4], 1);
    EXPECT_EQ(th->flags[5], 1);
    EXPECT_EQ(th->flags[6], 1);
    EXPECT_EQ(th->flag, 1);
}


TEST(handler, stock_trading_action) {

    unsigned char buffer[] = {
        0x48, // 'H' // 1 Byte Message Type
        0x32, 0x09, 0x01, 0x00, // 67890 // 4 byte timestamp
        0x41, 0x41, 0x50, 0x4C, 0x20, 0x20, 0x20, 0x20, // 8 byte stock 'AAPL    '
        0x54, // 1 byte trading State 'T' // Trading on NASDAQ
        0x00, // 1 byte reserved // Not sure lol
        0x44, 0x55, 0x43, 0x4B, // 4 byte reason , 'DUCK'
    };



    auto th = new test_handler;
    th->action(buffer, 19, 0);

    EXPECT_EQ(th->flags[0], 1);
    EXPECT_EQ(th->flags[1], 1);
    EXPECT_EQ(th->flags[2], 1);
    EXPECT_EQ(th->flags[3], 1);
    EXPECT_EQ(th->flags[6], 1);

}


TEST(handler, reg_sho_restriction) {

    unsigned char buffer[] = {
        'Y', // one byte message type
        0x32, 0x09, 0x01, 0x00, // 67890 // 4 byte timestamp
        0x41, 0x41, 0x50, 0x4C, 0x20, 0x20, 0x20, 0x20,
        '1' // short sale restriction in place.
    };

    auto th = new test_handler;
    th->action(buffer, 14, 0);


    EXPECT_EQ(th->flags[0], 1);
    EXPECT_EQ(th->flags[1], 1);
    EXPECT_EQ(th->flags[2], 1);
    EXPECT_EQ(th->flags[6], 1);

}


TEST(handler, market_participant_position) {

    unsigned char buffer[] = {
        'L', // 1 byte messageType
        0x32, 0x09, 0x01, 0x00, // 67890 // 4 byte timestamp
        0x32, 0x09, 0x01, 0x00, // 67890 // 4 byte MPID
        0x41, 0x41, 0x50, 0x4C, 0x20, 0x20, 0x20, 0x20, // AAPL 8 Byte Stock
        0x59, // primaryMarketMaker // 'Y'
        0x4E, // marketMakerMode // 'N' for normal.
        0x41, // market participation state // 'A' for active.
    };

    auto th = new test_handler;
    th->action(buffer, 20, 0);

    EXPECT_EQ(th->flags[0], 1);
    EXPECT_EQ(th->flags[1], 1);
    EXPECT_EQ(th->flags[2], 1);
    EXPECT_EQ(th->flags[3], 1);
    EXPECT_EQ(th->flags[4], 1);
    EXPECT_EQ(th->flags[5], 1);
    EXPECT_EQ(th->flags[6], 1);

}



TEST(handler, add_order_message) {

    unsigned char buffer[] = {
        'A', // messageType Add Order
        0x32, 0x09, 0x01, 0x00, // 67890 // 4 byte timestamp
        0x40, 0xE2, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, // 8 Byte reference number 123456
        'B', // Buy sell indicator 
        0x32, 0x09, 0x01, 0x00, // 67890 // 4 byte number of shares
        0x41, 0x41, 0x50, 0x4C, 0x20, 0x20, 0x20, 0x20, // 8 Byte AAPL stock,
        0x32, 0x09, 0x01, 0x00, // 6790 // 4 byte price.
    };


    auto th = new test_handler;
    th->action(buffer, 30, 0);


    EXPECT_EQ(th->flags[0], 1);
    EXPECT_EQ(th->flags[1], 1);
    EXPECT_EQ(th->flags[2], 1);
    EXPECT_EQ(th->flags[3], 1);
    EXPECT_EQ(th->flags[4], 1);
    EXPECT_EQ(th->flags[6], 1);
}


TEST(handler, malformed) {

    unsigned char buffer[] = {
        0x53,  // 'S' system event message
        0x00, 0x00, 0x00, 0x00,  // timestamp 0
        // 0x4F // no event code given!
    };

    auto th = new test_handler;

    th->action(buffer, 5, 0);

    EXPECT_EQ(th->flags[0], 0);
    EXPECT_EQ(th->flags[1], 0);
    EXPECT_EQ(th->flags[2], 0);
    EXPECT_EQ(th->flags[6], 0);

}