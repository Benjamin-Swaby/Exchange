#pragma once    

#include <utility>
#include <cstdint>
#include <cstddef>
#include <iostream>

namespace ouch {

    using std::pair;

    typedef unsigned char number[10];

    void toNumber(unsigned char* outprice, double price);

    std::pair<unsigned char*, size_t> toNumber(double price);

    std::ostream& operator<<(std::ostream& os, const number& num);

}