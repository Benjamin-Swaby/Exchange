#pragma once

#include <cstdint>


namespace outch {

    union symbol {
        char string[8];
        uint64_t i64;

        symbol(const char* s) {
            for (int i = 0; i < 8; i++) {
                this->string[i] = s[i];
            }
        }
    };


}