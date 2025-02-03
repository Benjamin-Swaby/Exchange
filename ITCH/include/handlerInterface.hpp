#include "itch.hpp"
#include <thread>
#include <vector>

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

            
            void start(const char* address, int port);

            void action(unsigned char* buffer, size_t size) {
                switch (buffer[0]) {
                    case 'S': if (size < sizeof(System_Event_Message)) return; handle(reinterpret_cast<System_Event_Message*>(buffer)); break;
                    case 'R': if (size < sizeof(Stock_Directory)) return; handle(reinterpret_cast<Stock_Directory*>(buffer)); break;
                    case 'H': if (size < sizeof(Stock_Trading_Action)) return; handle(reinterpret_cast<Stock_Trading_Action*>(buffer)); break;
                    case 'Y': if (size < sizeof(Reg_SHO_Restriction)) return; handle(reinterpret_cast<Reg_SHO_Restriction*>(buffer)); break;
                    case 'L': if (size < sizeof(Market_Participant_Position)) return; handle(reinterpret_cast<Market_Participant_Position*>(buffer)); break;
                    case 'A': if (size < sizeof(Add_Order_Message)) return; handle(reinterpret_cast<Add_Order_Message*>(buffer)); break;
                    case 'F': if (size < sizeof(Add_Order_MPID_Attribution)) return; handle(reinterpret_cast<Add_Order_MPID_Attribution*>(buffer)); break;
                    case 'E': if (size < sizeof(Order_Executed_Message)) return; handle(reinterpret_cast<Order_Executed_Message*>(buffer)); break;
                    case 'C': if (size < sizeof(Order_Executed_With_Price_Message)) return; handle(reinterpret_cast<Order_Executed_With_Price_Message*>(buffer)); break;
                    case 'X': if (size < sizeof(Order_Cancel_Message)) return; handle(reinterpret_cast<Order_Cancel_Message*>(buffer)); break;
                    case 'D': if (size < sizeof(Order_Delete_Message)) return; handle(reinterpret_cast<Order_Delete_Message*>(buffer)); break;
                    case 'U': if (size < sizeof(Order_Replace_Message)) return; handle(reinterpret_cast<Order_Replace_Message*>(buffer)); break;
                    case 'P': if (size < sizeof(Trade_Message)) return; handle(reinterpret_cast<Trade_Message*>(buffer)); break;
                    case 'Q': if (size < sizeof(Cross_Trade_Message)) return; handle(reinterpret_cast<Cross_Trade_Message*>(buffer)); break;
                    case 'B': if (size < sizeof(Broken_Trade_Message)) return; handle(reinterpret_cast<Broken_Trade_Message*>(buffer)); break;
                    case 'I': if (size < sizeof(NOII_Message)) return; handle(reinterpret_cast<NOII_Message*>(buffer)); break;
                    case 'N': if (size < sizeof(RPII_Message)) return; handle(reinterpret_cast<RPII_Message*>(buffer)); break;
                    default: return;
                }
            }

    };

}