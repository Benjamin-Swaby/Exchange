#include "include/stock_directory.hpp"
#include "include/time.hpp"

namespace ITCH41 {

    std::optional<ITCH41::Stock_Directory> new_StockDirectory(uint64_t stock, 
                                    uint8_t market_category, uint8_t financialStatusIndicator, 
                                    uint32_t roundLotSize, uint8_t roundLotsOnly) { 


        if (roundLotsOnly != 'Y' && roundLotsOnly != 'N') {
            return std::nullopt;
        }

        Stock_Directory sd;
        sd.messageType = 'R';
        sd.timestamp = nanoseconds_since_midnight();
        sd.stock = stock;
        sd.marketCategory = market_category;
        sd.financialStatusIndicator = financialStatusIndicator;
        sd.roundLotSize = roundLotSize;
        sd.roundLotsOnly = roundLotsOnly;

        return sd;

    }

}