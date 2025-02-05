#include <chrono>
#include <cstdint>
#include <array>

#include "include/time.hpp"

namespace ITCH41 {

    uint32_t nanoseconds_since_midnight() {
        using namespace std::chrono;

        auto now = system_clock::now();
        auto today = floor<days>(now);
        auto time_since_midnight = now - today;

        return static_cast<uint32_t>(duration_cast<nanoseconds>(time_since_midnight).count());
    }

}