#include <iostream>
#include <thread>

#include "include/itch.hpp"
#include "include/util.hpp"
#include "include/handlerInterface.hpp"
#include "include/clientInterface.hpp"


class Handler : public ITCH41::ITCH_Handler {

    void handle(ITCH41::System_Event_Message* msg, int socket) override {
        std::cout << "\n---- System Event Message ---- \n" << 
            "Message Type:\t" << msg->messageType << '\n' <<
            "TimeStamp:\t" << msg->timestamp << '\n' <<
            "Event Code:\t" << msg->eventCode << std::endl;
    }
    void handle(ITCH41::Stock_Directory* m, int socket) {return;}
    void handle(ITCH41::Stock_Trading_Action* m, int socket) {return;}
    void handle(ITCH41::Reg_SHO_Restriction* m, int socket) {return;}
    void handle(ITCH41::Market_Participant_Position* m, int socket) {return;}

    void handle(ITCH41::Add_Order_Message* m, int socket) {

        // Get String Representation of stock feild.
        ITCH41::STR_STOCK ss;
        ss.stock = m->stock;

        std::cout << "\n ---- Add Order Message ---- \n" <<
        "Message Type:\t" << m->messageType << '\n' <<
        "TimeStamp:\t" << m->timestamp << '\n' <<
        "Order Ref:\t" << m->orderReferenceNumber << '\n' <<
        "Side:\t\t" << m->buySellIndicator << '\n' <<
        "Shares:\t\t" << m->shares << '\n' <<
        "Stock:\t\t" << ss.str << '\n' <<
        "Price:\t\t" << m->price << std::endl;
    }

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
    
    void handle(const unsigned char* m, int socket) {
        std::cout << "Unknown Message Type " << m[0] << std::endl;
        unsigned char err[3] = {0x45, 0x52, 0x52};
        send_msg(err, socket);

    }
};

class Client : public ITCH41::ITCH_Client {

protected:
    void log(const unsigned char* msg) {
        std::cout << "Client -> \'" << msg[0] << "\'" << std::endl;
    }

public:
    void send_new_add_order_message() {
        

        ITCH41::STR_STOCK stock = {'A', 'A', 'P', 'L', ' ', ' ', ' ', ' '};
        auto aom = ITCH41::new_AddOrderMessage(123, 'B', 100, stock.stock, 456);

        if (aom.has_value())
            send_msg(aom.value().msg, sizeof(ITCH41::Add_Order_Message));

    }


};


int main(void) {

    auto h = new Handler;
    h->start("0.0.0.0", 5000);

    // wait a bit
    std::this_thread::sleep_for(std::chrono::seconds(1));

    auto c = new Client;
    c->start_session("0.0.0.0", 5000);
    
    // send 3 new add order messages // waiting 2 microseconds otherwise it's a bit eager to close the session.
    c->send_new_add_order_message();
    std::this_thread::sleep_for(std::chrono::microseconds(2)); 

    c->send_new_add_order_message();
    std::this_thread::sleep_for(std::chrono::microseconds(2));

    c->send_new_add_order_message();
    std::this_thread::sleep_for(std::chrono::microseconds(2));

    // close the session with the client
    c->stop_session();

    // wait for handler to finish;
    h->listenThread->join();

}