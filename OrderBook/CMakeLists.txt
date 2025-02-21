cmake_minimum_required(VERSION 3.10)

project(OrderBook)

enable_testing()

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Set CXX flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

include(FetchContent)
# Fetch Google Test

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)


add_library(OrderBook STATIC
    order.cpp
    orderbook.cpp
)

target_include_directories(OrderBook PUBLIC include)
target_link_libraries(OrderBook)

add_executable(OrderBook_test
    test/test_order.cpp
)

target_link_libraries(OrderBook_test gtest gtest_main pthread OrderBook)
include(GoogleTest)
gtest_discover_tests(OrderBook_test)