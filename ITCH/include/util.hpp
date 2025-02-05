#include "itch.hpp"
#include <fstream>
#include <filesystem>

namespace ITCH41 {

    void writeMsgToFile(const unsigned char* msg, size_t length, const char* filename) {
        std::ofstream file(filename, std::ios::out | std::ios::trunc | std::ios::binary);
        if (!file) {
            throw std::ios_base::failure("Failed to open file");
        }
        file.write(reinterpret_cast<const char*>(msg), length);
        if (!file) {
            throw std::ios_base::failure("Failed to write to file");
        }
    }



    typedef union convert {
        unsigned char str[8];
        uint64_t stock;
    } STR_STOCK;

    


}