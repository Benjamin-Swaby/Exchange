#pragma once

#include <cstdint>


namespace ouch {

    union symbol {
        char string[8];
        uint64_t i64;

        symbol(const char* s, size_t len) {

            len = len > 8 ? 8 : len;

            for (int i = 0; i < len; i++) {
                this->string[i] = s[i];
            }

            for (int i = len; i < 8; i++) {
                this->string[i] = 0;
            }

        }
    };


}