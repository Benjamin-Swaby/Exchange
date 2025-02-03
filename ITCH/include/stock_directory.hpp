#pragma once

#include "../include/itch.hpp"

#include <optional>
#include <cstdint>

namespace ITCH41 {

    std::optional<ITCH41::Stock_Directory> new_StockDirectory(uint64_t stock, uint8_t market_category, uint8_t financialStatusIndicator, uint32_t roundLotSize, uint8_t roundLotsOnly);

}