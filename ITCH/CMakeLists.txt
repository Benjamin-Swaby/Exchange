cmake_minimum_required(VERSION 3.10)

# Set the project name
project(ITCH)

enable_testing()

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Set CXX flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

include(FetchContent)


# Add the library
add_library(ITCH STATIC 
    itch.cpp 
    time.cpp
    handlerInterface.cpp
    clientInterface.cpp
)

# Include directories
target_include_directories(ITCH PUBLIC include)
target_link_libraries(ITCH)

# Fetch Google Test

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

# Add test executable
add_executable(ITCH_test 
    test/test_system_event_message.cpp
    test/test_handler.cpp
    test/test_stock_directory.cpp
)


target_link_libraries(ITCH_test gtest gtest_main pthread ITCH)

include(GoogleTest)
gtest_discover_tests(ITCH_test)



add_executable(ITCH_Example
    main.cpp
)
target_link_libraries(ITCH_Example ITCH)
 
