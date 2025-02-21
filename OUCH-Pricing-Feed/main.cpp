#include "include/message.hpp"
#include "include/number.hpp"
#include "include/time.hpp"

#include <algorithm>
#include <iostream>


int main(void) {

    outch::message msg("AAPL", 123.456, 321.654);

    std::cout << msg << std::endl;

    return 0;

}