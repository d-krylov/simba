#include "tools.h"
#include "print_strings.h"
#include <cstdio>
#include <string>

int PrintGlobalHeader(global_header &h, uint64_t offset, char *out) {
#if DEBUG == 1
  return std::printf(gh.data(), offset, h.magic_number, h.version_major,
                     h.version_minor, h.thiszone, h.sigfigs, h.snaplen,
                     h.network);
#else
  return std::sprintf(out, gh.data(), offset, h.magic_number, h.version_major,
                      h.version_minor, h.thiszone, h.sigfigs, h.snaplen,
                      h.network);
#endif
}

int PrintPacketHeader(packet_header &h, uint64_t offset, char *out) {
#if DEBUG == 1
  return std::printf(ph.data(), offset, h.ts_sec, h.ts_usec, h.incl_len,
                     h.orig_len);
#else
  return std::sprintf(out, ph.data(), offset, h.ts_sec, h.ts_usec, h.incl_len,
                      h.orig_len);
#endif
}

int PrintUdp(udp &h, uint64_t offset, char *out) {
#if DEBUG == 1
  return std::printf(udph.data(), offset, SB(h.SourcePort),
                     SB(h.DestinationPort), SB(h.Length), SB(h.Checksum));
#else
  return std::sprintf(out, udph.data(), offset, SB(h.SourcePort),
                      SB(h.DestinationPort), SB(h.Length), SB(h.Checksum));
#endif
}

int PrintMarketDataPacketHeader(market_data_packet_header &h, uint64_t offset,
                                char *out) {
#if DEBUG == 1
  return std::printf(mdph.data(), offset, h.MsgSeqNum, h.MsgSize, h.MsgFlags,
                     h.SendingTime);
#else
  return std::sprintf(out, mdph.data(), offset, h.MsgSeqNum, h.MsgSize,
                      h.MsgFlags, h.SendingTime);
#endif
}

int PrintIncrementalPacketHeader(incremental_packet_header &h, uint64_t offset,
                                 char *out) {
#if DEBUG == 1
  return std::printf(iph.data(), offset, h.TransactTime,
                     h.ExchangeTradingSessionID);
#else
  return std::sprintf(out, iph.data(), offset, h.TransactTime,
                      h.ExchangeTradingSessionID);
#endif
}

int PrintSbeHeader(sbe_header &h, uint64_t offset, char *out) {
#if DEBUG == 1
  return std::printf(sbeh.data(), offset, h.BlockLength, h.TemplateID,
                     h.SchemaID, h.Version);
#else
  return std::sprintf(out, sbeh.data(), offset, h.BlockLength, h.TemplateID,
                      h.SchemaID, h.Version);
#endif
}

int PrintOrderUpdate(order_update &h, uint64_t offset, char *out) {
#if DEBUG == 1
  return std::printf(ou.data(), offset, h.MDEntryID, h.MDEntryPx.mantissa,
                     h.MDEntrySize, h.MDFlags, h.SecurityID, h.RptSeq,
                     h.MDUpdateAction, h.MDEntryType);
#else
  return std::sprintf(out, ou.data(), offset, h.MDEntryID, h.MDEntryPx.mantissa,
                      h.MDEntrySize, h.MDFlags, h.SecurityID, h.RptSeq,
                      h.MDUpdateAction, h.MDEntryType);
#endif
}

int PrintOrderBookSnapshot(order_book_snapshot &h, uint64_t offset, char *out) {
#if DEBUG == 1
  return std::printf(obs.data(), offset, h.SecurityID, h.LastMsgSeqNumProcessed,
                     h.RptSeq, h.ExchangeTradingSessionID,
                     h.NoMDEntries.blockLength, h.NoMDEntries.numInGroup);
#else
  return std::printf(out, obs.data(), offset, h.SecurityID,
                     h.LastMsgSeqNumProcessed, h.RptSeq,
                     h.ExchangeTradingSessionID, h.NoMDEntries.blockLength,
                     h.NoMDEntries.numInGroup);
#endif
}

int PrintMDEntry(MDEntries &h, uint64_t offset, char *out) {
#if DEBUG == 1
  return std::printf(mde.data(), offset, h.MDEntryID, h.TransactTime,
                     h.MDEntryPx.mantissa, h.MDEntrySize, h.TradeID, h.MDFlags,
                     h.MDEntryType);
#else
  return std::sprintf(out, mde.data(), offset, h.MDEntryID, h.TransactTime,
                      h.MDEntryPx.mantissa, h.MDEntrySize, h.TradeID, h.MDFlags,
                      h.MDEntryType);
#endif
}

int PrintOrderExecution(order_execution &h, uint64_t offset, char *out) {
#if DEBUG == 1
  return std::printf(oe.data(), offset, h.MDEntryID, h.MDEntryPx.mantissa,
                     h.MDEntrySize, h.LastPx.mantissa, h.LastQty, h.TradeID,
                     h.MDFlags, h.SecurityID, h.RptSeq, h.MDUpdateAction,
                     h.MDEntryType);
#else
  return std::sprintf(out, oe.data(), offset, h.MDEntryID, h.MDEntryPx.mantissa,
                      h.MDEntrySize, h.LastPx.mantissa, h.LastQty, h.TradeID,
                      h.MDFlags, h.SecurityID, h.RptSeq, h.MDUpdateAction,
                      h.MDEntryType);
#endif
}

int PrintBestPrices(best_prices &h, uint64_t offset, char *out) {
#if DEBUG == 1
  return std::printf(bp.data(), offset, h.MktBidPx.mantissa,
                     h.MktOfferPx.mantissa, h.BPFlags, h.SecurityID);
#else
  return std::sprintf(out, bp.data(), offset, h.MktBidPx.mantissa,
                      h.MktOfferPx.mantissa, h.BPFlags, h.SecurityID);
#endif
}

int PrintTradingSessionStatus(trading_session_status &h, uint64_t offset,
                              char *out) {
#if DEBUG == 1
  return std::printf(trading_session.data(), offset, h.TradSesOpenTime,
                     h.TradSesCloseTime, h.TradSesIntermClearingStartTime,
                     h.TradSesIntermClearingEndTime, h.MarketSegmentId,
                     h.ExchangeTradingSessionID, h.TradSesStatus, h.MarketId,
                     h.MarketSegmentId, h.TradSesEvent);
#else
  return std::sprintf(out, trading_session.data(), offset, h.TradSesOpenTime,
                      h.TradSesCloseTime, h.TradSesIntermClearingStartTime,
                      h.TradSesIntermClearingEndTime, h.MarketSegmentId,
                      h.ExchangeTradingSessionID, h.TradSesStatus, h.MarketId,
                      h.MarketSegmentId, h.TradSesEvent);
#endif
}

bool CheckMsgId(uint16_t msg_id) {
  return (msg_id >= 3 && msg_id <= 7) || (msg_id >= 9 && msg_id <= 13) ||
         (msg_id == 1002);
}

void GetSpecifierFromType() {}