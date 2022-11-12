#include "tools.h"
#include "print_strings.h"
#include <cstdio>
#include <string>


void PrintGlobalHeader(global_header &h, uint64_t offset) {
  std::printf(gh.data(), offset, h.magic_number, h.version_major, h.version_minor,
              h.thiszone, h.sigfigs, h.snaplen, h.network);
}

void PrintPacketHeader(packet_header &h, uint64_t offset) {
  std::printf(ph.data(), offset, h.ts_sec, h.ts_usec, h.incl_len, h.orig_len);
}

void PrintUdp(udp &h, uint64_t offset) {
  std::printf(udph.data(), offset, SB(h.SourcePort), SB(h.DestinationPort),
              SB(h.Length), SB(h.Checksum));
}

void PrintMarketDataPacketHeader(market_data_packet_header &h,
                                 uint64_t offset) {
  std::printf(mdph.data(), offset, h.MsgSeqNum, h.MsgSize, h.MsgFlags, h.SendingTime);
}

void PrintIncrementalPacketHeader(incremental_packet_header &h,
                                  uint64_t offset) {
  std::printf(iph.data(), offset, h.TransactTime, h.ExchangeTradingSessionID);
}

void PrintSbeHeader(sbe_header &h, uint64_t offset) {
  std::printf(sbeh.data(), offset, h.BlockLength, h.TemplateID, h.SchemaID, h.Version);
}

void PrintOrderUpdate(order_update &h, uint64_t offset) {
  std::printf(ou.data(), offset, h.MDEntryID, h.MDEntryPx.mantissa, h.MDEntrySize,
              h.MDFlags, h.SecurityID, h.RptSeq, h.MDUpdateAction,
              h.MDEntryType);
}

void PrintOrderBookSnapshot(order_book_snapshot &h, uint64_t offset) {
  std::printf(obs.data(), offset, h.SecurityID, h.LastMsgSeqNumProcessed, h.RptSeq,
              h.ExchangeTradingSessionID, h.NoMDEntries.blockLength,
              h.NoMDEntries.numInGroup);
}

void PrintMDEntry(MDEntries &h, uint64_t offset) {
  std::printf(mde.data(), offset, h.MDEntryID, h.TransactTime, h.MDEntryPx.mantissa,
              h.MDEntrySize, h.TradeID, h.MDFlags, h.MDEntryType);
}

void PrintOrderExecution(order_execution &h, uint64_t offset) {
  std::printf(oe.data(), offset, h.MDEntryID, h.MDEntryPx.mantissa, h.MDEntrySize,
              h.LastPx.mantissa, h.LastQty, h.TradeID, h.MDFlags, h.SecurityID,
              h.RptSeq, h.MDUpdateAction, h.MDEntryType);
}

void PrintBestPrices(best_prices &h, uint64_t offset) {
  std::printf(bp.data(), offset, h.MktBidPx.mantissa, h.MktOfferPx.mantissa, h.BPFlags,
              h.SecurityID);
}

void PrintTradingSessionStatus(trading_session_status &h, uint64_t offset) {
  std::printf(trading_session.data(), offset, h.TradSesOpenTime, h.TradSesCloseTime,
              h.TradSesIntermClearingStartTime, h.TradSesIntermClearingEndTime,
              h.MarketSegmentId, h.ExchangeTradingSessionID, h.TradSesStatus,
              h.MarketId, h.MarketSegmentId, h.TradSesEvent);
}

bool CheckMsgId(uint16_t msg_id) {
  return (msg_id >= 3 && msg_id <= 7) || (msg_id >= 9 && msg_id <= 13) ||
         (msg_id == 1002);
}

void GetSpecifierFromType() {}