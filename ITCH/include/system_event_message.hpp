#pragma once

#include "itch.hpp"
#include <optional>

namespace ITCH41 {
    
    std::optional<System_Event_Message> new_SystemEventMessage(unsigned char eventCode);
    
}