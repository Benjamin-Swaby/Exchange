#include <gtest/gtest.h>
#include "../include/itch.hpp"




TEST(system_event_message_test, new_SystemEventMessage) {

    // Valid Event Codes:
    // O, S, Q, M, E, C, A, R, B

    char validEventCodes[] = {'O', 'S', 'Q', 'M', 'E', 'C', 'A', 'R', 'B'};

    for (int i = 0; i < sizeof(validEventCodes); i++) {
        auto msg = ITCH41::new_SystemEventMessage(validEventCodes[i]);

        if (!msg.has_value()) {
            FAIL() << "Invalid Event Code: " << validEventCodes[i];
        }

        EXPECT_EQ(msg.value().messageType, 'S');
        EXPECT_EQ(msg.value().eventCode, validEventCodes[i]);
    }

    // Invalid Event Codes:

    char invalidEventCodes[] = {'Z', 'X', 'Y', 'L', 'K', 'J', 'I', 'H', 'G'};

    for (int i = 0; i < sizeof(invalidEventCodes); i++) {
        auto msg = ITCH41::new_SystemEventMessage(invalidEventCodes[i]);

        if (msg.has_value()) {
            FAIL() << "Valid Event Code: " << invalidEventCodes[i];
        }
    }


}


TEST(system_event_message_test, buffer_read) {
    unsigned char buffer[] = {0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4F}; // Example ITCH system_event_message

    ITCH41::System_Event_Message msg;
    memcpy(&msg, buffer, 6);

    EXPECT_EQ(msg.messageType, 'S');
    EXPECT_EQ(msg.timestamp, 0);
    EXPECT_EQ(msg.eventCode, 'O');
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}