#include "include/itch.hpp"
#include "./include/system_event_message.hpp"
#include "./include/time.hpp"

#include <optional>


namespace ITCH41 {

    std::optional<System_Event_Message> new_SystemEventMessage(unsigned char eventCode) {

        // check if eventCode is valid.
        switch (eventCode) {
            case 'O': // Start of Messages
            case 'S': // Start of System Hours
            case 'Q': // Start of Market Hours
            case 'M': // End of Market Hours
            case 'E': // End of System Hours
            case 'C': // End of Messages

            case 'A': // Emergancy Market Condition (EMC in effect, No trading allowed.)
            case 'R': // Emergancy Market Condition (Quote Only)
            case 'B': // Emergancy Market Condition (Resumed)
                break;
            default:
                return std::nullopt;
        }


        System_Event_Message msg;
        msg.messageType = 'S';
        msg.timestamp = nanoseconds_since_midnight();
        msg.eventCode = eventCode;
        return msg;
    }

}