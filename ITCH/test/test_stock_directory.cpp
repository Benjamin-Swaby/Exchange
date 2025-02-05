#include <gtest/gtest.h>
#include "../include/itch.hpp"



const char valid_market_category[] = {'N', 'A', 'P', 'Q', 'G', 'S', 'Z'};
const char valid_fsi[8] = {'D', 'E', 'Q', 'S', 'G', 'H', 'J', 'K'};
const char valid_rlo[2] = {'Y', 'N'}; 
const uint64_t aapl = 1280328001; // 8 byte representation of "AAPL    ";


TEST(stock_directory, new_stock_directory) {

    auto sd = ITCH41::new_StockDirectory(aapl, *valid_market_category, *valid_fsi, 10, *valid_rlo);

    if (sd.has_value()) {
        ASSERT_EQ(sd.value().messageType, 'R');
        ASSERT_EQ(sd.value().stock, aapl);
        ASSERT_EQ(sd.value().marketCategory, *valid_market_category);
        ASSERT_EQ(sd.value().financialStatusIndicator, *valid_fsi);
        ASSERT_EQ(sd.value().roundLotSize, 10);
        ASSERT_EQ(sd.value().roundLotsOnly, *valid_rlo);
    } else {
        FAIL() << "Failed to create stock directory";
    }

}

TEST(stock_directory, new_stock_directory_valid_fsi) {

    for (const char* fsi = valid_fsi; fsi != (valid_fsi + 8); fsi++) {

        auto sd = ITCH41::new_StockDirectory(aapl, *valid_market_category, *fsi, 10, *valid_rlo);
        
        if (!sd.has_value())
            FAIL() << "Stock Directory Should Have Valid FSI";
        SUCCEED();
    }

}

TEST(stock_directory, new_stock_directory_valid_market_category) {

    for (const char* mc = valid_market_category; mc != (valid_market_category + 7); mc++) {

        auto sd = ITCH41::new_StockDirectory(aapl, *mc, *valid_fsi, 10, *valid_rlo);
        
        if (!sd.has_value())
            FAIL() << "Stock Directory Should Have Valid Market Category";
        SUCCEED();
    }

}

TEST(stock_directory, new_stock_directory_valid_rlo) {

    for (const char* rlo = valid_rlo; rlo != (valid_rlo + 2); rlo++) {

        auto sd = ITCH41::new_StockDirectory(aapl, *valid_market_category, *valid_fsi, 10, *rlo);
        
        if (!sd.has_value())
            FAIL() << "Stock Directory Should Have Valid RLO";
        SUCCEED();
    }

}


TEST(stock_directory, new_stock_directory_invalid_rlo) {

    const char invalid_rlo[] = {'X', 'Z', '1', '0'};

    for (const char* rlo = invalid_rlo; rlo != (invalid_rlo + 4); rlo++) {

        auto sd = ITCH41::new_StockDirectory(aapl, *valid_market_category, *valid_fsi, 10, *rlo);
        
        if (sd.has_value())
            FAIL() << "Stock Directory Should Not Have Valid RLO";
        SUCCEED();
    }

}

TEST(stock_directory, new_stock_directory_invalid_market_category) {

    const char invalid_market_category[] = {'X', 'Y', '1', '2'};

    for (const char* mc = invalid_market_category; mc != (invalid_market_category + 4); mc++) {

        auto sd = ITCH41::new_StockDirectory(aapl, *mc, *valid_fsi, 10, *valid_rlo);
        
        if (sd.has_value())
            FAIL() << "Stock Directory Should Not Have Valid Market Category";
        SUCCEED();
    }

}

TEST(stock_directory, new_stock_directory_invalid_fsi) {

    const char invalid_fsi[] = {'X', 'Y', '1', '2'};

    for (const char* fsi = invalid_fsi; fsi != (invalid_fsi + 4); fsi++) {

        auto sd = ITCH41::new_StockDirectory(aapl, *valid_market_category, *fsi, 10, *valid_rlo);
        
        if (sd.has_value())
            FAIL() << "Stock Directory Should Not Have Valid FSI";
        SUCCEED();
    }

}

