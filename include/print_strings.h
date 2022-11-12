#ifndef PRINT_STRINGS_H
#define PRINT_STRINGS_H

#include <string>
#include <string_view>

constexpr std::string_view gh =
"[ %#016x ]\033[0;32m Global Header: \033[0m             \
 [ magic number: 0x%x; \
 version major: %d; \
 version minor: %d; \
 thiszone: 0x%x; \
 sigfigs: 0x%x; \
 snaplen: 0x%x; \
 network: %d ]\n"; 

constexpr std::string_view ph = 
"[ %#016x ] \033[0;32m Packet Header: \033[0m             \
 [ ts_sec: %d; \
 ts_usec: %d; \
 incl_len: %d; \
 orig_len: %d ]\n";

constexpr std::string_view udph = 
"[ %#016x ] \033[0;32m UDP Header: \033[0m                \
 [ Source Port: %d; \
 Destination Port: %d; \
 Length: %d; \
 Checksum: 0x%x ]\n";

constexpr std::string_view mdph = 
"[ %#016x ] \033[0;31m Market Data Packet Header: \033[0m \
 [ MsgSeqNum: %d; \
 MsgSize: %d; \
 MsgFlags: 0x%x; \
 SendingTime: %llu ]\n";

constexpr std::string_view iph = 
"[ %#016x ] \033[0;31m Incremental Packet Header: \033[0m \
 [ TransactTime: %llu; \
 ExchangeTradingSessionID: %d ]\n";

constexpr std::string_view sbeh = 
"[ %#016x ] \033[0;31m SBE Header: \033[0m                \
 [ BlockLength: %d; \
 TemplateID: %d; \
 SchemaID: %d; \
 Version: %d ]\n";

constexpr std::string_view ou = 
"[ %#016x ] \033[0;31m Order Update: \033[0m              \
 [ MDEntryID: %lld; \
 MDEntryPx.mantissa: %llu; \
 MDEntrySize: %lld; \
 MDFlags: %llu; \
 SecurityID: %d; \
 RptSeq: %u; \
 MDUpdateAction: %u; \
 MDEntryType: %u ]\n";

constexpr std::string_view oe = 
"[ %#016x ] \033[0;31m Order Execution: \033[0m           \
 [ MDEntryID: %lld; \
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
"[ %#016x ] \033[0;31m Order Book Snapshot: \033[0m       \
 [ SecurityID: %d; \
 LastMsgSeqNumProcessed: %u; \
 RptSeq: %d; \
 ExchangeTradingSessionID: %u; \
 NoMDEntries.blockLength: %d; \
 NoMDEntries.numInGroup - %d ]\n";

constexpr std::string_view mde = 
"[ %#016x ] \033[0;34m MDEntries: \033[0m                 \
 [ MDEntryID: %llu; \
 TransactTime: %llu; \
 MDEntryPx.mantissa: %lld; \
 MDEntrySize: %d; \
 TradeID: %d; \
 MDFlags: %d; \
 MDEntryType: %u ]\n";

constexpr std::string_view bp = 
"[ %#016x ] \033[0;31m Best Prices: \033[0m               \
 [ MktBidPx.mantissa: %d; \
 MktOfferPx.mantissa: %d; \
 BPFlags: %u; \
 SecurityID: %u ]\n";

constexpr std::string_view trading_session =
"[ %#016x ] \033[0;31m Trading Session Status: \033[0m    \
 [ TradSesOpenTime: %llu; \
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
