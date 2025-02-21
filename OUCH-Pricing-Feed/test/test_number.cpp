#include <gtest/gtest.h>

#include "../include/number.hpp"

bool compare(const unsigned char* a, const unsigned char* b) {
    for(int i = 0; i < 10; i++) {
        if(a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

TEST(number_test, eq) {
    unsigned char a[10] = {1,2,3,4,5,6,7,8,9,0};
    unsigned char b[10] = {1,2,3,4,5,6,7,8,9,0};

    EXPECT_TRUE(compare(a, b));
    EXPECT_TRUE(compare(b, a));
    EXPECT_TRUE(compare(a, a));

}

TEST(number_test, vaild_number) {

    // Valid Inputs
    double validNumber = 123.456;
    
    ouch::number out = {0,0,0,0,0,0,0,0,0,0};
    ouch::toNumber(out, validNumber);
    unsigned char expected[10] = {0,0,0,1,2,3,4,5,6,0};
    
    std::cout << out << std::endl;

    EXPECT_TRUE(compare(out, expected));

}


TEST(test_number, filled_number) {

    // Valid Inputs
    double filledNumber = 123456.1234;
        
    ouch::number out = {0,0,0,0,0,0,0,0,0,0};
    ouch::toNumber(out, filledNumber);
    unsigned char expected[10] = {1,2,3,4,5,6,1,2,3,4};

    std::cout << out << std::endl;

    EXPECT_TRUE(compare(out, expected));

}


TEST(test_number, max_number) {

    double maxNumber = 999999.9999;

    ouch::number out = {0,0,0,0,0,0,0,0,0,0};
    ouch::toNumber(out, maxNumber);
    unsigned char expected[10] = {9,9,9,9,9,9,9,9,9,9};

    EXPECT_TRUE(compare(out, expected));
}


TEST(test_number, min_number) {
    double minNumber = 0.0;

    ouch::number out = {0,0,0,0,0,0,0,0,0,0};
    ouch::toNumber(out, minNumber);
    unsigned char expected[10] = {0,0,0,0,0,0,0,0,0,0};

    EXPECT_TRUE(compare(out, expected));

}


TEST(test_number, negative_number) {
    double negativeNumber = -123.456;

    ouch::number out = {0,0,0,0,0,0,0,0,0,0};
    ouch::toNumber(out, negativeNumber);
    unsigned char expected[10] = {0,0,0,0,0,0,0,0,0,0};

    EXPECT_TRUE(compare(out, expected));

}


TEST(test_number, too_big_number) {
    double tooBigNumber = 1234567.1234;

    ouch::number out = {0,0,0,0,0,0,0,0,0,0};
    ouch::toNumber(out, tooBigNumber);
    unsigned char expected[10] = {0,0,0,0,0,0,0,0,0,0};

    EXPECT_TRUE(compare(out, expected));
}

TEST(test_number, too_big_decimal) {
    double tooBigDecimal = 123.123456;

    ouch::number out = {0,0,0,0,0,0,0,0,0,0};
    ouch::toNumber(out, tooBigDecimal);
    unsigned char expected[10] = {0,0,0,1,2,3,1,2,3,4};

    EXPECT_TRUE(compare(out, expected));
}