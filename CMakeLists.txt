cmake_minimum_required(VERSION 3.10)

project(Exchange)

enable_testing()

add_subdirectory(ITCH)
add_subdirectory(OUCH-Pricing-Feed)
add_subdirectory(OrderBook)

# Assuming you have a main executable target called Exchange
add_executable(Exchange 
    main.cpp
)

# Link the ITCH and OUCH-Pricing-Feed libraries to your main executable
target_link_libraries(Exchange PRIVATE ITCH OUCH-PF)

# Include the directories for ITCH and OUCH-Pricing-Feed
target_include_directories(Exchange PRIVATE
    ${CMAKE_SOURCE_DIR}/ITCH/include
    ${CMAKE_SOURCE_DIR}/OUCH-Pricing-Feed/include
)
