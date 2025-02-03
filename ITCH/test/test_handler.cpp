#include<gtest/gtest.h>

#include "../include/itch.hpp"
#include "../include/handlerInterface.hpp"

using namespace ITCH41;

class test_handler : public ITCH41::ITCH_Handler {
public:
    int flag = 0;

    void handle(ITCH41::System_Event_Message* msg) override {
        flag = (msg->eventCode == 'O' && msg->timestamp == 0 && msg->messageType == 'S');
    }

    void handle(Stock_Directory* m) {return;}
    void handle(Stock_Trading_Action* m) {return;}
    void handle(Reg_SHO_Restriction* m) {return;}
    void handle(Market_Participant_Position* m) {return;}
    void handle(Add_Order_Message* m) {return;}
    void handle(Add_Order_MPID_Attribution* m) {return;}
    void handle(Order_Executed_Message* m) {return;}
    void handle(Order_Executed_With_Price_Message* m) {return;}
    void handle(Order_Cancel_Message* m) {return;}
    void handle(Order_Delete_Message* m) {return;}
    void handle(Order_Replace_Message* m) {return;}
    void handle(Trade_Message* m) {return;}
    void handle(Cross_Trade_Message* m) {return;}
    void handle(Broken_Trade_Message* m) {return;}
    void handle(NOII_Message* m) {return;}
    void handle(RPII_Message* m) {return;}
};


TEST(handler, system_event_message) {

    unsigned char buffer[] = {0x53, 0x00, 0x00, 0x00, 0x00, 0x4F};
    auto th = new test_handler;

    // calling action on the buffer should handle this as a System_Event_Message
    // This if done correctly will set the flag attribute in th to 1
    th->action(buffer);

    EXPECT_EQ(th->flag, 1);


}