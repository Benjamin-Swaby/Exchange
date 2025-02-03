/***
 * itch.hpp
 * 
 * This file contains definitions of various ITCH message types.
 * They are formed of unions such that data can be read into msg attributes
 * 
 * i.e to recieve a System_Event_Message, you can read the raw data into the msg attribute
 * 
 * System_Event_Message* msg;
 * sock.recv(msg->msg, sizeof(msg.msg), 0);
 * 
 * Then you can access the attributes of the message
 * msg->timestamp;
 * msg->eventCode; 
 * 
 * 
 * These message types are correct to the ITCH 4.1 specification
 * https://www.nasdaqtrader.com/content/technicalsupport/specifications/dataproducts/nqtv-itch-v4_1.pdf
 */



#pragma once

#include <cstdint>
#include <cstring>

namespace ITCH41 {

    #pragma pack(push, 1)
    union System_Event_Message {
        unsigned char msg[6];
        struct {
            uint8_t messageType;
            uint32_t timestamp;
            uint8_t eventCode;
        };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    union Stock_Directory {
        unsigned char msg[20];
        struct {
            uint8_t messageType;
            uint32_t timestamp;
            uint64_t stock;
            uint8_t marketCategory;
            uint8_t financialStatusIndicator;
            uint32_t roundLotSize;
            uint8_t roundLotsOnly;
        };
    };
    #pragma pack(pop)


    #pragma pack(push, 1)
    union Stock_Trading_Action {
        unsigned char msg[19];
        struct {
            uint8_t messageType;
            uint32_t timestamp;
            uint64_t stock;
            uint8_t tradingState;
            uint8_t reserved;
            uint32_t reason;
        };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    union Reg_SHO_Restriction {
        unsigned char msg[14];
        struct {
            uint8_t messageType;
            uint32_t timestamp;
            uint64_t stock;
            uint8_t regSHOAction;
        };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    union Market_Participant_Position {
        unsigned char msg[20];
        struct {
            uint8_t messageType;
            uint32_t timestamp;
            uint32_t MPID;
            uint64_t stock;
            uint8_t primaryMarketMaker;
            uint8_t marketMakerMode;
            uint8_t marketParticipantState;
        };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    union Add_Order_Message {
        unsigned char msg[30];
        struct {
            uint8_t messageType;
            uint32_t timestamp;
            uint64_t orderReferenceNumber;
            uint8_t buySellIndicator;
            uint32_t shares;
            uint64_t stock;
            uint32_t price;
        };
    };
    #pragma pack(pop)

    typedef Add_Order_Message Add_Order_No_MPID_Attribution; 

    #pragma pack(push, 1)
    union Add_Order_MPID_Attribution {
        unsigned char msg[34];
        struct {
            uint8_t messageType;
            uint32_t timestamp;
            uint64_t orderReferenceNumber;
            uint8_t buySellIndicator;
            uint32_t shares;
            uint64_t stock;
            uint32_t price;
            uint32_t attribution;
        };
    };
    #pragma pack(pop)



    #pragma pack(push, 1)
    union Order_Executed_Message {
        unsigned char msg[25];
        struct {
            uint8_t messageType;
            uint32_t timestamp;
            uint64_t orderReferenceNumber;
            uint32_t executedShares;
            uint64_t matchNumber;
        };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    union Order_Executed_With_Price_Message {
        unsigned char msg[30];
        struct {
            uint8_t messageType;
            uint32_t timestamp;
            uint64_t orderReferenceNumber;
            uint32_t executedShares;
            uint64_t matchNumber;
            uint8_t printable;
            uint32_t price;
        };
    };
    #pragma pack(pop)


    #pragma pack(push, 1)
    union Order_Cancel_Message {
        unsigned char msg[17];
        struct {
            uint8_t messageType;
            uint32_t timestamp;
            uint64_t orderReferenceNumber;
            uint32_t canceledShares;
        };
    };
    #pragma pack(pop)  

    #pragma pack(push, 1)
    union Order_Delete_Message {
        unsigned char msg[13];
        struct {
            uint8_t messageType;
            uint32_t timestamp;
            uint64_t orderReferenceNumber;
        };
    };
    #pragma pack(pop)


    #pragma pack(push, 1)
    union Order_Replace_Message {
        unsigned char msg[29];
        struct {
            uint8_t messageType;
            uint32_t timestamp;
            uint64_t originalOrderReferenceNumber;
            uint64_t newOrderReferenceNumber;
            uint32_t shares;
            uint32_t price;
        };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    union Trade_Message {
        unsigned char msg[30];
        struct {
            uint8_t messageType;
            uint32_t timestamp;
            uint64_t matchNumber;
            uint8_t buySellIndicator;
            uint32_t shares;
            uint64_t stock;
            uint32_t price;
        };

    };
    #pragma pack(pop)  

    #pragma pack(push, 1)
    union Cross_Trade_Message {
        unsigned char msg[26];
        struct {
            uint8_t messageType;
            uint32_t timestamp;
            uint64_t matchNumber;
            uint8_t crossType;
            uint32_t shares;
            uint64_t stock;
            uint32_t crossPrice;
        };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    union Broken_Trade_Message {
        unsigned char msg[13];
        struct {
            uint8_t messageType;
            uint32_t timestamp;
            uint64_t matchNumber;
        };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    union NOII_Message {
        unsigned char msg[44];
        struct {
            uint8_t messageType;
            uint32_t timestamp;
            uint64_t pairedShares;
            uint64_t imbalanceShares;
            uint8_t imbalanceDirection;
            uint64_t stock;
            uint32_t farPrice;
            uint32_t nearPrice;
            uint32_t currentReferencePrice;
            uint8_t crossType;
            uint8_t priceVariationIndicator;
        };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    union RPII_Message {
        unsigned char msg[22];
        struct {
            uint8_t messageType;
            uint32_t timestamp;
            uint64_t stock;
            uint8_t interestFlag;
            uint8_t price;
        };
    };
    #pragma pack(pop)
}






