#include <gtest/gtest.h>
#include "simba.h"
#include "tools.h"

TEST(MarketDataPacketHeaderTest, BasicAssertions) {
    uint8_t buffer[] = {0xf4, 0x4e, 0x6a, 0x02, 0x4e, 0x00, 0x09, 0x00, 
                        0x4c, 0xb3, 0x28, 0xa9, 0xc6, 0x39, 0xb6, 0x16};

    auto hdr = GetMarketDataPacketHeader(buffer);

    ASSERT_EQ(hdr->MsgSeqNum, 40521460);
    ASSERT_EQ(hdr->MsgSize, 78);
    ASSERT_EQ(hdr->MsgFlags, 0x9);
    ASSERT_EQ(hdr->SendingTime, 1636559040000078668);
}

TEST(IncrementalPacketHeaderTest, BasicAssertions) {
    uint8_t buffer[] = {0xb1, 0x8a, 0x28, 0xa9, 0xc6, 0x39, 0xb6, 0x16,
                        0x11, 0x19, 0x00, 0x00};

    auto hdr = GetIncrementalPacketHeader(buffer);

    ASSERT_EQ(hdr->TransactTime, 1636559040000068273);
    ASSERT_EQ(hdr->ExchangeTradingSessionID, 6417);
}

TEST(SbeHeaderTest, BasicAssertions) {

    uint8_t buffer[] = {0x2a, 0x00, 0x05, 0x00, 0x44, 0x4d, 0x00, 0x00};

    auto hdr = GetSbeHeader(buffer);

    ASSERT_EQ(hdr->BlockLength, 42);
    ASSERT_EQ(hdr->TemplateID, 5);
    ASSERT_EQ(hdr->SchemaID, 19780);
    ASSERT_EQ(hdr->Version, 0);
}

TEST(OrderUpdateTest, BasicAssertions) {
    uint8_t buffer[] = {0xf0, 0x24, 0x40, 0x00, 0x11, 0x19, 0x36, 0x1b,
                        0xd0, 0xef, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
                        0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                        0x01, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
                        0xd1, 0x0a, 0x1f, 0x00, 0xef, 0x61, 0x36, 0x00,
                        0x02, 0x31};

    auto hdr = GetOrderUpdate(buffer);

    ASSERT_EQ(hdr->MDEntryID, 1960782248575771888);
    ASSERT_EQ(hdr->MDEntryPx.mantissa, 8450000);
    ASSERT_EQ(hdr->MDEntrySize, 65);
    ASSERT_EQ(hdr->SecurityID, 2034385);
    ASSERT_EQ(hdr->RptSeq, 3564015);
    ASSERT_EQ(hdr->MDUpdateAction, UpdateAction::Delete);
    ASSERT_EQ(hdr->MDEntryType, '1');
}

TEST(OrderExecutionTest, BasicAssertions) {
    
}