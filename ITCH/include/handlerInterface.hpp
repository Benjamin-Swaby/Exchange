#include "itch.hpp"
#include <thread>


namespace ITCH41 {

        class ITCH_Handler {
        private:
            int socketID;
        public:
            std::thread* listenThread;

            virtual void handle(System_Event_Message* m, int socket) = 0;
            virtual void handle(Stock_Directory* m, int socket) = 0;
            virtual void handle(Stock_Trading_Action* m, int socket) = 0;
            virtual void handle(Reg_SHO_Restriction* m, int socket) = 0;
            virtual void handle(Market_Participant_Position* m, int socket) = 0;
            virtual void handle(Add_Order_Message* m, int socket) = 0;
            virtual void handle(Add_Order_MPID_Attribution* m, int socket) = 0;
            virtual void handle(Order_Executed_Message* m, int socket) = 0;
            virtual void handle(Order_Executed_With_Price_Message* m, int socket) = 0;
            virtual void handle(Order_Cancel_Message* m, int socket) = 0;
            virtual void handle(Order_Delete_Message* m, int socket) = 0;
            virtual void handle(Order_Replace_Message* m, int socket) = 0;
            virtual void handle(Trade_Message* m, int socket) = 0;
            virtual void handle(Cross_Trade_Message* m, int socket) = 0;
            virtual void handle(Broken_Trade_Message* m, int socket) = 0;
            virtual void handle(NOII_Message* m, int socket) = 0;
            virtual void handle(RPII_Message* m, int socket) = 0;
            virtual void handle(const unsigned char* m, int socket) = 0;
            

            void start(const char* address, int port);
            void send_msg(unsigned char* msg, int socket);

            void action(unsigned char* buffer, size_t size, int socket);

            ~ITCH_Handler();

    };

}