#ifndef PRINT_STRINGS_H
#define PRINT_STRINGS_H

#include <string>
#include <string_view>

constexpr std::string_view gh =
"[ %#016x ]" FRED("  Global Header:                 ") \
"[ magic number: 0x%x; \
 version major: %d; \
 version minor: %d; \
 thiszone: 0x%x; \
 sigfigs: 0x%x; \
 snaplen: 0x%x; \
 network: %d ]\n"; 

constexpr std::string_view ph = 
"[ %#016x ]" FRED("  Packet Header:               ") \
"[ ts_sec: %d; \
 ts_usec: %d; \
 incl_len: %d; \
 orig_len: %d ]\n";

constexpr std::string_view udph = 
"[ %#016x ]" FGRN("  UDP Header:                  ") \
"[ Source Port: %d; \
 Destination Port: %d; \
 Length: %d; \
 Checksum: 0x%x ]\n";

constexpr std::string_view mdph = 
"[ %#016x ]" FMAG("  Market Data Packet Header:   ") \
"[ MsgSeqNum: %d; \
 MsgSize: %d; \
 MsgFlags: 0x%x; \
 SendingTime: %llu ]\n";

constexpr std::string_view iph = 
"[ %#016x ]" FMAG("  Incremental Packet Header:   ") \
"[ TransactTime: %llu; \
 ExchangeTradingSessionID: %d ]\n";

constexpr std::string_view sbeh = 
"[ %#016x ]" FMAG("  SBE Header:                  ") \
"[ BlockLength: %d; \
 TemplateID: %d; \
 SchemaID: %d; \
 Version: %d ]\n";

constexpr std::string_view ou = 
"[ %#016x ]" FMAG("  Order Update:                ") \
"[ MDEntryID: %lld; \
 MDEntryPx.mantissa: %llu; \
 MDEntrySize: %lld; \
 MDFlags: %llu; \
 SecurityID: %d; \
 RptSeq: %u; \
 MDUpdateAction: %u; \
 MDEntryType: %u ]\n";

constexpr std::string_view oe = 
"[ %#016x ]" FMAG("  Order Execution:             ") \
"[ MDEntryID: %lld; \
 MDEntryPx.mantissa: %lld; \
 MDEntrySize: %lld; \
 LastPx.mantissa: %lld; \
 LastQty: %lld; \
 TradeID: %lld; \
 MDFlags: %lld; \
 SecurityID: %d; \
 RptSeq: %d; \
 MDUpdateAction: %u; \
 MDEntryType: %u ]\n";

constexpr std::string_view obs = 
"[ %#016x ]" FMAG("  Order Book Snapshot:         ") \
"[ SecurityID: %d; \
 LastMsgSeqNumProcessed: %u; \
 RptSeq: %d; \
 ExchangeTradingSessionID: %u; \
 NoMDEntries.blockLength: %d; \
 NoMDEntries.numInGroup - %d ]\n";

constexpr std::string_view mde = 
"[ %#016x ]" FBLU("  MDEntries:                   ") \
"[ MDEntryID: %llu; \
 TransactTime: %llu; \
 MDEntryPx.mantissa: %lld; \
 MDEntrySize: %d; \
 TradeID: %d; \
 MDFlags: %d; \
 MDEntryType: %u ]\n";

constexpr std::string_view bp = 
"[ %#016x ]" FBLU("Best Prices:                   ") \
"[ MktBidPx.mantissa: %d; \
 MktOfferPx.mantissa: %d; \
 BPFlags: %u; \
 SecurityID: %u ]\n";

constexpr std::string_view trading_session =
"[ %#016x ]" FRED("  Trading Session Status:      ") \
"[ TradSesOpenTime: %llu; \
 TradSesCloseTime: %llu; \
 TradSesIntermClearingStartTime: %llu; \
 TradSesIntermClearingEndTime: %llu \
 TradingSessionId: %u \
 ExchangeTradingSessionID: %u \
 TradSesStatus: %u \
 MarketId: %u \
 MarketSegmentId: %u \
 TradSesEvent: %u ]\n";

#endif // PRINT_STRINGS_H
