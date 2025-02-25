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
#include <optional>

namespace ITCH41 {

    #pragma pack(push, 1)
    union System_Event_Message {
        unsigned char msg[10];
        struct {
            uint8_t messageType;
            uint64_t timestamp;
            uint8_t eventCode;
        };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    union Stock_Directory {
        unsigned char msg[24];
        struct {
            uint8_t messageType;
            uint64_t timestamp;
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
        unsigned char msg[23];
        struct {
            uint8_t messageType;
            uint64_t timestamp;
            uint64_t stock;
            uint8_t tradingState;
            uint8_t reserved;
            uint32_t reason;
        };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    union Reg_SHO_Restriction {
        unsigned char msg[18];
        struct {
            uint8_t messageType;
            uint64_t timestamp;
            uint64_t stock;
            uint8_t regSHOAction;
        };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    union Market_Participant_Position {
        unsigned char msg[24];
        struct {
            uint8_t messageType;
            uint64_t timestamp;
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
        unsigned char msg[34];
        struct {
            uint8_t messageType;
            uint64_t timestamp;
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
        unsigned char msg[38];
        struct {
            uint8_t messageType;
            uint64_t timestamp;
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
        unsigned char msg[29];
        struct {
            uint8_t messageType;
            uint64_t timestamp;
            uint64_t orderReferenceNumber;
            uint32_t executedShares;
            uint64_t matchNumber;
        };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    union Order_Executed_With_Price_Message {
        unsigned char msg[34];
        struct {
            uint8_t messageType;
            uint64_t timestamp;
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
        unsigned char msg[21];
        struct {
            uint8_t messageType;
            uint64_t timestamp;
            uint64_t orderReferenceNumber;
            uint32_t canceledShares;
        };
    };
    #pragma pack(pop)  

    #pragma pack(push, 1)
    union Order_Delete_Message {
        unsigned char msg[17];
        struct {
            uint8_t messageType;
            uint64_t timestamp;
            uint64_t orderReferenceNumber;
        };
    };
    #pragma pack(pop)


    #pragma pack(push, 1)
    union Order_Replace_Message {
        unsigned char msg[33];
        struct {
            uint8_t messageType;
            uint64_t timestamp;
            uint64_t originalOrderReferenceNumber;
            uint64_t newOrderReferenceNumber;
            uint32_t shares;
            uint32_t price;
        };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    union Trade_Message {
        unsigned char msg[34];
        struct {
            uint8_t messageType;
            uint64_t timestamp;
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
        unsigned char msg[34];
        struct {
            uint8_t messageType;
            uint64_t timestamp;
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
        unsigned char msg[17];
        struct {
            uint8_t messageType;
            uint64_t timestamp;
            uint64_t matchNumber;
        };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    union NOII_Message {
        unsigned char msg[48];
        struct {
            uint8_t messageType;
            uint64_t timestamp;
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
        unsigned char msg[26];
        struct {
            uint8_t messageType;
            uint64_t timestamp;
            uint64_t stock;
            uint8_t interestFlag;
            uint8_t price;
        };
    };
    #pragma pack(pop)

    std::optional<System_Event_Message> new_SystemEventMessage(unsigned char eventCode);
    std::optional<Stock_Directory> new_StockDirectory(uint64_t stock, uint8_t market_category, uint8_t financialStatusIndicator, uint32_t roundLotSize, uint8_t roundLotsOnly);
    std::optional<Stock_Trading_Action> new_StockTradingAction(uint64_t stock, uint8_t tradingState, uint8_t reserved, uint32_t reason);
    std::optional<Reg_SHO_Restriction> new_Reg_SHO_Restriction(uint64_t stock, uint8_t regSHOAction);
    std::optional<Market_Participant_Position> new_MarketParticipantPosition(uint32_t MPID, uint64_t stock, uint8_t primaryMarketMaker, uint8_t MarketMakerMode, uint8_t marketMakerParticipantState);
    std::optional<Add_Order_Message> new_AddOrderMessage(uint64_t orderReferenceNumber, uint8_t buySellIndicator, uint32_t shares, uint64_t stock, uint32_t price);
    std::optional<Add_Order_MPID_Attribution> new_AddOrderMPIDAttribution(uint64_t orderReferenceNumber, uint8_t buySellIndicator, uint32_t shares, uint64_t stock, uint32_t price, uint32_t attribution);
    std::optional<Order_Executed_Message> new_OrderExecutedMessage(uint64_t orderReferenceNumber, uint32_t executedShares, uint64_t matchNumber);
    std::optional<Order_Executed_With_Price_Message> new_OrderExecutedWithPriceMessage(uint64_t orderReferenceNumber, uint32_t executedShares, uint64_t matchNumber, uint8_t printable, uint32_t price);
    std::optional<Order_Cancel_Message> new_OrderCancelMessage(uint64_t orderReferenceNumber, uint32_t canceledShares);
    std::optional<Order_Delete_Message> new_OrderDeleteMessage(uint64_t orderReferenceNumber);
    std::optional<Order_Replace_Message> new_OrderReplaceMessage(uint64_t originalOrderReferenceNumber, uint64_t newOrderReferenceNumber, uint32_t shares, uint32_t price);
    std::optional<Trade_Message> new_TradeMessage(uint64_t matchNumber, uint8_t buySellIndicator, uint32_t shares, uint64_t stock, uint32_t price);
    std::optional<Cross_Trade_Message> new_CrossTradeMessage(uint64_t matchNumber, uint8_t crossType, uint32_t shares, uint64_t stock, uint32_t crossPrice);
    std::optional<Broken_Trade_Message> new_BrokenTradeMessage(uint64_t matchNumber);
    std::optional<NOII_Message> new_NOIIMessage(uint64_t pairedShares, uint64_t imbalanceShares, uint8_t imbalanceDirection, uint64_t stock, uint32_t farPrice, uint32_t nearPrice, uint32_t currentReferencePrice, uint8_t crossType, uint8_t priceVariationIndicator);
    std::optional<RPII_Message> new_RPIIMessage(uint64_t stock, uint8_t interestFlag, uint8_t price);
}






