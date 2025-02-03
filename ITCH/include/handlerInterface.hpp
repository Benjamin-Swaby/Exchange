#include "itch.hpp"

namespace ITCH41 {

        class ITCH_Handler {

        public:

            virtual void handle(System_Event_Message* m) = 0;
            virtual void handle(Stock_Directory* m) = 0;
            virtual void handle(Stock_Trading_Action* m) = 0;
            virtual void handle(Reg_SHO_Restriction* m) = 0;
            virtual void handle(Market_Participant_Position* m) = 0;
            virtual void handle(Add_Order_Message* m) = 0;
            virtual void handle(Add_Order_MPID_Attribution* m) = 0;
            virtual void handle(Order_Executed_Message* m) = 0;
            virtual void handle(Order_Executed_With_Price_Message* m) = 0;
            virtual void handle(Order_Cancel_Message* m) = 0;
            virtual void handle(Order_Delete_Message* m) = 0;
            virtual void handle(Order_Replace_Message* m) = 0;
            virtual void handle(Trade_Message* m) = 0;
            virtual void handle(Cross_Trade_Message* m) = 0;
            virtual void handle(Broken_Trade_Message* m) = 0;
            virtual void handle(NOII_Message* m) = 0;
            virtual void handle(RPII_Message* m) = 0;

            
            void action(unsigned char* buffer) {
                switch (buffer[0]) {
                    case 'S': handle(reinterpret_cast<System_Event_Message*>(buffer)); break;
                    case 'R': handle(reinterpret_cast<Stock_Directory*>(buffer)); break;
                    case 'H': handle(reinterpret_cast<Stock_Trading_Action*>(buffer)); break;
                    case 'Y': handle(reinterpret_cast<Reg_SHO_Restriction*>(buffer)); break;
                    case 'L': handle(reinterpret_cast<Market_Participant_Position*>(buffer)); break;
                    case 'A': handle(reinterpret_cast<Add_Order_Message*>(buffer)); break;
                    case 'F': handle(reinterpret_cast<Add_Order_MPID_Attribution*>(buffer)); break;
                    case 'E': handle(reinterpret_cast<Order_Executed_Message*>(buffer)); break;
                    case 'C': handle(reinterpret_cast<Order_Executed_With_Price_Message*>(buffer)); break;
                    case 'X': handle(reinterpret_cast<Order_Cancel_Message*>(buffer)); break;
                    case 'D': handle(reinterpret_cast<Order_Delete_Message*>(buffer)); break;
                    case 'U': handle(reinterpret_cast<Order_Replace_Message*>(buffer)); break;
                    case 'P': handle(reinterpret_cast<Trade_Message*>(buffer)); break;
                    case 'Q': handle(reinterpret_cast<Cross_Trade_Message*>(buffer)); break;
                    case 'B': handle(reinterpret_cast<Broken_Trade_Message*>(buffer)); break;
                    case 'I': handle(reinterpret_cast<NOII_Message*>(buffer)); break;
                    case 'N': handle(reinterpret_cast<RPII_Message*>(buffer)); break;
                    default: return;
                }
            }

    };

}