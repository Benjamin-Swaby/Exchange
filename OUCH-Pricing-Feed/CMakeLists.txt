cmake_minimum_required(VERSION 3.10)

project(OUCH-PF)

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


add_library(OUCH-PF STATIC
    time.cpp
    ouch.cpp
    number.cpp
)

target_include_directories(OUCH-PF PUBLIC include)
target_link_libraries(OUCH-PF)

add_executable(OUCH_test
    test/test_message.cpp
    test/test_number.cpp
)


target_link_libraries(OUCH_test gtest gtest_main pthread OUCH-PF)

include(GoogleTest)
gtest_discover_tests(OUCH_test)



add_executable(OUCH_Example
    main.cpp
)

target_link_libraries(OUCH_Example OUCH-PF)
 
