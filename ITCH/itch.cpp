#include <iostream>

#include "include/itch.hpp"
#include "include/time.hpp"


namespace ITCH41 {

    std::optional<System_Event_Message> new_SystemEventMessage(unsigned char eventCode) {

        // check if eventCode is valid.
        switch (eventCode) {
            case 'O': // Start of Messages
            case 'S': // Start of System Hours
            case 'Q': // Start of Market Hours
            case 'M': // End of Market Hours
            case 'E': // End of System Hours
            case 'C': // End of Messages

            case 'A': // Emergancy Market Condition (EMC in effect, No trading allowed.)
            case 'R': // Emergancy Market Condition (Quote Only)
            case 'B': // Emergancy Market Condition (Resumed)
                break;
            default:
                return std::nullopt;
        }


        System_Event_Message msg;
        msg.messageType = 'S';
        msg.timestamp = nanoseconds_since_midnight();
        msg.eventCode = eventCode;
        return msg;
    }


    std::optional<ITCH41::Stock_Directory> new_StockDirectory(uint64_t stock, 
                                    uint8_t market_category, uint8_t financialStatusIndicator, 
                                    uint32_t roundLotSize, uint8_t roundLotsOnly) { 


        if (roundLotsOnly != 'Y' && roundLotsOnly != 'N') {
            return std::nullopt;
        }

        switch(market_category) {
            case 'N':
            case 'A':
            case 'P':
            case 'Q':
            case 'G':
            case 'S':
            case 'Z':
                break;
            default:
                return std::nullopt;
        }

        switch(financialStatusIndicator) {
            case 'D':
            case 'E':
            case 'Q':
            case 'S':
            case 'G':
            case 'H':
            case 'J':
            case 'K':
                break;
            default:
                return std::nullopt;
        }


        Stock_Directory sd;
        sd.messageType = 'R';
        sd.timestamp = nanoseconds_since_midnight();
        sd.stock = stock;
        sd.marketCategory = market_category;
        sd.financialStatusIndicator = financialStatusIndicator;
        sd.roundLotSize = roundLotSize;
        sd.roundLotsOnly = roundLotsOnly;

        return sd;

    }



    std::optional<ITCH41::Stock_Trading_Action> new_StockTradingAction(uint64_t stock, uint8_t tradingState, 
                                                                            uint8_t reserved, uint32_t reason) {


        switch (tradingState) {
            case 'H':
            case 'P':
            case 'Q':
            case 'T':
                break;
            default:
                return std::nullopt;    
        }

        ITCH41::Stock_Trading_Action sta;
        sta.messageType = 'H';
        sta.timestamp = nanoseconds_since_midnight();
        sta.stock = stock;
        sta.tradingState = tradingState;
        sta.reserved = reserved;
        sta.reason = reason;                                                                       

        return sta;
    }


    std::optional<Reg_SHO_Restriction> new_Reg_SHO_Restriction(uint64_t stock, uint8_t regSHOAction) {

        switch (regSHOAction) {
            case '0':
            case '1':
            case '2':
                break;
            default:
                return std::nullopt;
        }

        Reg_SHO_Restriction rshor;
        rshor.messageType = 'Y';
        rshor.timestamp = nanoseconds_since_midnight();
        rshor.stock = stock;
        rshor.regSHOAction = regSHOAction;
        return rshor;

    }

    std::optional<Market_Participant_Position> new_MarketParticipantPosition(uint32_t MPID, uint64_t stock, uint8_t primaryMarketMaker, uint8_t MarketMakerMode, uint8_t marketMakerParticipantState) {

        if(primaryMarketMaker != 'Y' && primaryMarketMaker != 'N')
            return std::nullopt;
        
        switch (MarketMakerMode) {
            case 'N': // Normal
            case 'P': // Passive
            case 'S': // Syndicate
            case 'R': // Pre-Syndicate
            case 'L': // Penalty
                break;
            default:
                return std::nullopt;
        }

        switch (marketMakerParticipantState) {
            case 'A': // Active
            case 'E': // Excused/Withdrawn
            case 'W': // Withdrawn
            case 'S': // Suspended
            case 'D': // Deleted
                break;
            default:
                return std::nullopt;
        }

        Market_Participant_Position mpp;
        mpp.messageType = 'L';
        mpp.timestamp = nanoseconds_since_midnight();
        mpp.MPID = MPID;
        mpp.stock = stock;
        mpp.primaryMarketMaker = primaryMarketMaker;
        mpp.marketMakerMode = MarketMakerMode;
        mpp.marketParticipantState = marketMakerParticipantState;

        return mpp;

    }
    std::optional<Add_Order_Message> new_AddOrderMessage(uint64_t orderReferenceNumber, uint8_t buySellIndicator, uint32_t shares, uint64_t stock, uint32_t price) {
        if (buySellIndicator != 'B' && buySellIndicator != 'S') {
            return std::nullopt;
        }

        Add_Order_Message aom;
        aom.messageType = 'A';
        aom.timestamp = nanoseconds_since_midnight();
        aom.orderReferenceNumber = orderReferenceNumber;
        aom.buySellIndicator = buySellIndicator;
        aom.shares = shares;
        aom.stock = stock;
        aom.price = price;

        return aom;
    }
    std::optional<Add_Order_MPID_Attribution> new_AddOrderMPIDAttribution(uint64_t orderReferenceNumber, uint8_t buySellIndicator, uint32_t shares, uint64_t stock, uint32_t price, uint32_t attribution) {
        if (buySellIndicator != 'B' && buySellIndicator != 'S') {
            return std::nullopt;
        }

        Add_Order_MPID_Attribution aoma;
        aoma.messageType = 'F';
        aoma.timestamp = nanoseconds_since_midnight();
        aoma.orderReferenceNumber = orderReferenceNumber;
        aoma.buySellIndicator = buySellIndicator;
        aoma.shares = shares;
        aoma.stock = stock;
        aoma.price = price;
        aoma.attribution = attribution;

        return aoma;
    }

    std::optional<Order_Executed_Message> new_OrderExecutedMessage(uint64_t orderReferenceNumber, uint32_t executedShares, uint64_t matchNumber) {
        Order_Executed_Message oem;
        oem.messageType = 'E';
        oem.timestamp = nanoseconds_since_midnight();
        oem.orderReferenceNumber = orderReferenceNumber;
        oem.executedShares = executedShares;
        oem.matchNumber = matchNumber;

        return oem;
    }

    std::optional<Order_Executed_With_Price_Message> new_OrderExecutedWithPriceMessage(uint64_t orderReferenceNumber, uint32_t executedShares, uint64_t matchNumber, uint8_t printable, uint32_t price) {
        if (printable != 'Y' && printable != 'N') {
            return std::nullopt;
        }

        Order_Executed_With_Price_Message oewpm;
        oewpm.messageType = 'C';
        oewpm.timestamp = nanoseconds_since_midnight();
        oewpm.orderReferenceNumber = orderReferenceNumber;
        oewpm.executedShares = executedShares;
        oewpm.matchNumber = matchNumber;
        oewpm.printable = printable;
        oewpm.price = price;

        return oewpm;
    }

    std::optional<Order_Cancel_Message> new_OrderCancelMessage(uint64_t orderReferenceNumber, uint32_t canceledShares) {
        Order_Cancel_Message ocm;
        ocm.messageType = 'X';
        ocm.timestamp = nanoseconds_since_midnight();
        ocm.orderReferenceNumber = orderReferenceNumber;
        ocm.canceledShares = canceledShares;

        return ocm;
    }

    std::optional<Order_Delete_Message> new_OrderDeleteMessage(uint64_t orderReferenceNumber) {
        Order_Delete_Message odm;
        odm.messageType = 'D';
        odm.timestamp = nanoseconds_since_midnight();
        odm.orderReferenceNumber = orderReferenceNumber;

        return odm;
    }

    std::optional<Order_Replace_Message> new_OrderReplaceMessage(uint64_t originalOrderReferenceNumber, uint64_t newOrderReferenceNumber, uint32_t shares, uint32_t price) {
        if (shares == 0 || price == 0) {
            return std::nullopt;
        }

        Order_Replace_Message orm;
        orm.messageType = 'U';
        orm.timestamp = nanoseconds_since_midnight();
        orm.originalOrderReferenceNumber = originalOrderReferenceNumber;
        orm.newOrderReferenceNumber = newOrderReferenceNumber;
        orm.shares = shares;
        orm.price = price;

        return orm;
    }
    std::optional<Trade_Message> new_TradeMessage(uint64_t matchNumber, uint8_t buySellIndicator, uint32_t shares, uint64_t stock, uint32_t price) {
        if (buySellIndicator != 'B' && buySellIndicator != 'S') {
            return std::nullopt;
        }

        Trade_Message tm;
        tm.messageType = 'P';
        tm.timestamp = nanoseconds_since_midnight();
        tm.matchNumber = matchNumber;
        tm.buySellIndicator = buySellIndicator;
        tm.shares = shares;
        tm.stock = stock;
        tm.price = price;

        return tm;
    }

    std::optional<Cross_Trade_Message> new_CrossTradeMessage(uint64_t matchNumber, uint8_t crossType, uint32_t shares, uint64_t stock, uint32_t crossPrice) {
        if (crossType != 'O' && crossType != 'C') {
            return std::nullopt;
        }

        Cross_Trade_Message ctm;
        ctm.messageType = 'Q';
        ctm.timestamp = nanoseconds_since_midnight();
        ctm.matchNumber = matchNumber;
        ctm.crossType = crossType;
        ctm.shares = shares;
        ctm.stock = stock;
        ctm.crossPrice = crossPrice;

        return ctm;
    }

    std::optional<Broken_Trade_Message> new_BrokenTradeMessage(uint64_t matchNumber) {
        Broken_Trade_Message btm;
        btm.messageType = 'B';
        btm.timestamp = nanoseconds_since_midnight();
        btm.matchNumber = matchNumber;

        return btm;
    }

    std::optional<NOII_Message> new_NOIIMessage(uint64_t pairedShares, uint64_t imbalanceShares, uint8_t imbalanceDirection, uint64_t stock, uint32_t farPrice, uint32_t nearPrice, uint32_t currentReferencePrice, uint8_t crossType, uint8_t priceVariationIndicator) {
        if (imbalanceDirection != 'B' && imbalanceDirection != 'S' && imbalanceDirection != 'N') {
            return std::nullopt;
        }
        if (crossType != 'O' && crossType != 'C') {
            return std::nullopt;
        }

        NOII_Message noii;
        noii.messageType = 'I';
        noii.timestamp = nanoseconds_since_midnight();
        noii.pairedShares = pairedShares;
        noii.imbalanceShares = imbalanceShares;
        noii.imbalanceDirection = imbalanceDirection;
        noii.stock = stock;
        noii.farPrice = farPrice;
        noii.nearPrice = nearPrice;
        noii.currentReferencePrice = currentReferencePrice;
        noii.crossType = crossType;
        noii.priceVariationIndicator = priceVariationIndicator;

        return noii;
    }

    std::optional<RPII_Message> new_RPIIMessage(uint64_t stock, uint8_t interestFlag, uint8_t price) {
        if (interestFlag != 'B' && interestFlag != 'S') {
            return std::nullopt;
        }

        RPII_Message rpii;
        rpii.messageType = 'N';
        rpii.timestamp = nanoseconds_since_midnight();
        rpii.stock = stock;
        rpii.interestFlag = interestFlag;
        rpii.price = price;

        return rpii;
    }


}