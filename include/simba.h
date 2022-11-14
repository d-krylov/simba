#ifndef SIMBA_H
#define SIMBA_H

#include "simba_types.h"
#include <stdio.h>

#define FLAG_INCREMENTAL (0x8)

struct market_data_packet_header {
  uint32_t MsgSeqNum;
  uint16_t MsgSize;
  uint16_t MsgFlags;
  uint64_t SendingTime;
  int Print(uint64_t offset, FILE *out);
} PACKED;

struct incremental_packet_header {
  uint64_t TransactTime;
  uint32_t ExchangeTradingSessionID;
  int Print(uint64_t offset, FILE *out);
} PACKED;


struct sbe_header {
  uint16_t BlockLength;
  uint16_t TemplateID;
  uint16_t SchemaID;
  uint16_t Version;
  int Print(uint64_t offset, FILE *out);
} PACKED;

enum UpdateAction { New = 0, Change, Delete };

struct order_update {
  int64_t MDEntryID;
  Decimal5 MDEntryPx;
  int64_t MDEntrySize;
  uint64_t MDFlags;
  int32_t SecurityID;
  uint32_t RptSeq;
  uint8_t MDUpdateAction;
  char MDEntryType;
  int Print(uint64_t offset, FILE *out);
} PACKED;

struct order_execution {
  int64_t MDEntryID;
  Decimal5NULL MDEntryPx;
  int64_t MDEntrySize;
  Decimal5 LastPx;
  int64_t LastQty;
  int64_t TradeID;
  uint64_t MDFlags;
  int32_t SecurityID;
  uint32_t RptSeq;
  uint8_t MDUpdateAction;
  char MDEntryType;
  int Print(uint64_t offset, FILE *out);
} PACKED;

struct MDEntries {
  int64_t MDEntryID;
  uint64_t TransactTime;
  Decimal5NULL MDEntryPx;
  int64_t MDEntrySize;
  int64_t TradeID;
  uint64_t MDFlags;
  char MDEntryType;
  int Print(uint64_t offset, FILE *out);
} PACKED;

struct order_book_snapshot {
  int32_t SecurityID;
  uint32_t LastMsgSeqNumProcessed;
  uint32_t RptSeq;
  uint32_t ExchangeTradingSessionID;
  group_size NoMDEntries;
  int Print(uint64_t offset, FILE *out);
} PACKED;

struct best_prices {
  Decimal5NULL MktBidPx;
  Decimal5NULL MktOfferPx;
  uint8_t BPFlags;
  int32_t SecurityID;
  int Print(uint64_t offset, FILE *out);
} PACKED;

struct trading_session_status {
  uint64_t TradSesOpenTime;
  uint64_t TradSesCloseTime;
  uint64_t TradSesIntermClearingStartTime;
  uint64_t TradSesIntermClearingEndTime;
  uint8_t TradingSessionId;
  uint32_t ExchangeTradingSessionID;
  uint8_t TradSesStatus;
  char MarketId;
  char MarketSegmentId;
  uint8_t TradSesEvent;
  int Print(uint64_t offset, FILE *out);
} PACKED;


struct SecurityDefinition
{
  uint32_t TotNumReports;
  String25 Symbol;
  int32_t SecurityID;
  int Print(uint64_t offset, FILE *out);
} PACKED;

struct sequence_reset { 
  int32_t NewSeqNo;
  int Print(uint64_t offset, FILE *out);
} PACKED;

struct security_definition_update_report {
  int32_t SecurityID;
  char SecurityIdSource;
  Decimal5NULL Volatility;
  Decimal5NULL TheorPrice;
  Decimal5NULL TheorPriceLimit;
  int Print(uint64_t offset, FILE *out);
} PACKED;

struct empty_book {

} PACKED;

/* Functions */

inline std::size_t GetSBESize() {
  return sizeof(sbe_header);
}

inline std::size_t GetMDPHSize() {
  return sizeof(market_data_packet_header);
}

inline std::size_t GetIPHSize() {
  return sizeof(incremental_packet_header);
}

inline std::size_t GetOBSSize() {
  return sizeof(order_book_snapshot);
}

inline std::size_t GetOUSize() {
  return sizeof(order_update);
}

inline std::size_t GetTSSSize() {
  return sizeof(trading_session_status);
}

inline market_data_packet_header *
GetMarketDataPacketHeader(char *ptr) {
  return reinterpret_cast<market_data_packet_header *>(ptr);
}

inline incremental_packet_header *
GetIncrementalPacketHeader(char *ptr) {
  return reinterpret_cast<incremental_packet_header *>(ptr);
}

inline sbe_header *GetSbeHeader(char *ptr) {
  return reinterpret_cast<sbe_header *>(ptr);
}

inline order_update *GetOrderUpdate(char *ptr) {
  return reinterpret_cast<order_update *>(ptr);
}

inline order_execution *GetOrderExecution(char *ptr) {
  return reinterpret_cast<order_execution *>(ptr);
}

inline group_size *GetGroupSize(char *ptr) {
  return reinterpret_cast<group_size *>(ptr);
}

inline MDEntries *GetMDEntries(char *ptr) {
  return reinterpret_cast<MDEntries *>(ptr);
}

inline order_book_snapshot *GetOrderBookSnapshot(char *ptr) {
  return reinterpret_cast<order_book_snapshot *>(ptr);
}

inline best_prices *GetBestPrices(char *ptr) {
  return reinterpret_cast<best_prices *>(ptr);
}

inline trading_session_status *GetTradingSessionStatus(char *ptr) {
  return reinterpret_cast<trading_session_status *>(ptr);
}

/* Assertions */

static_assert(sizeof(market_data_packet_header) == 16);
static_assert(sizeof(sbe_header) == 8);
static_assert(sizeof(incremental_packet_header) == 12);
static_assert(sizeof(order_update) == 42);
static_assert(sizeof(order_book_snapshot) == 19);
static_assert(sizeof(MDEntries) == 49);
static_assert(sizeof(order_execution) == 66);
static_assert(sizeof(best_prices) == 21);

#endif // SIMBA_H