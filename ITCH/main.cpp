#include <iostream>
#include <thread>

#include "include/itch.hpp"
#include "include/handlerInterface.hpp"


class Handler : public ITCH41::ITCH_Handler {

    void handle(ITCH41::System_Event_Message* msg, int socket) override {
        std::cout << "\n---- System Event Message ---- \n" << 
            "Message Type:\t" << msg->messageType << '\n' <<
            "TimeStamp:\t" << msg->timestamp << '\n' <<
            "Event Code:\t" << msg->eventCode << std::endl;

        
        auto sem = ITCH41::new_SystemEventMessage('O');
        send_msg(sem.value().msg, socket);

    }
    void handle(ITCH41::Stock_Directory* m, int socket) {return;}
    void handle(ITCH41::Stock_Trading_Action* m, int socket) {return;}
    void handle(ITCH41::Reg_SHO_Restriction* m, int socket) {return;}
    void handle(ITCH41::Market_Participant_Position* m, int socket) {return;}
    void handle(ITCH41::Add_Order_Message* m, int socket) {return;}
    void handle(ITCH41::Add_Order_MPID_Attribution* m, int socket) {return;}
    void handle(ITCH41::Order_Executed_Message* m, int socket) {return;}
    void handle(ITCH41::Order_Executed_With_Price_Message* m, int socket) {return;}
    void handle(ITCH41::Order_Cancel_Message* m, int socket) {return;}
    void handle(ITCH41::Order_Delete_Message* m, int socket) {return;}
    void handle(ITCH41::Order_Replace_Message* m, int socket) {return;}
    void handle(ITCH41::Trade_Message* m, int socket) {return;}
    void handle(ITCH41::Cross_Trade_Message* m, int socket) {return;}
    void handle(ITCH41::Broken_Trade_Message* m, int socket) {return;}
    void handle(ITCH41::NOII_Message* m, int socket) {return;}
    void handle(ITCH41::RPII_Message* m, int socket) {return;}
};

int main(void) {

    auto h = new Handler;
    h->start("0.0.0.0", 5000);

}