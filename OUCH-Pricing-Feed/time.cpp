#include <chrono>
#include <cstdint>
#include <array>

#include "include/time.hpp"

namespace ouch {

    uint64_t nanoseconds_since_midnight() {
        using namespace std::chrono;

        auto now = system_clock::now();
        auto today = floor<days>(now);
        auto time_since_midnight = now - today;

        return static_cast<uint64_t>(duration_cast<nanoseconds>(time_since_midnight).count());
    }

}