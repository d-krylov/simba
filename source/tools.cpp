#include "tools.h"
#include "global.h"
#include "pcap.h"
#include "print_strings.h"
#include "simba.h"
#include <cstdio>

int global_header::Print(uint64_t offset, FILE *out) {
  return LOG(out, gh.data(), offset, magic_number, version_major, version_minor,
             thiszone, sigfigs, snaplen, network);
}

int packet_header::Print(uint64_t offset, FILE *out) {
  return LOG(out, ph.data(), offset, ts_sec, ts_usec, incl_len, orig_len);
}

int ip_header::Print(uint64_t offset, FILE *out) {
  //return LOG(out);
}

int udp_header::Print(uint64_t offset, FILE *out) {
  return LOG(out, udph.data(), offset, SB(SourcePort), SB(DestinationPort),
             SB(Length), SB(Checksum));
}

int market_data_packet_header::Print(uint64_t offset, FILE *out) {
  return LOG(out, mdph.data(), offset, MsgSeqNum, MsgSize, MsgFlags,
             SendingTime);
}

int incremental_packet_header::Print(uint64_t offset, FILE *out) {
  return LOG(out, iph.data(), offset, TransactTime, ExchangeTradingSessionID);
}

int sbe_header::Print(uint64_t offset, FILE *out) {
  return LOG(out, sbeh.data(), offset, BlockLength, TemplateID, SchemaID,
             Version);
}

int order_update::Print(uint64_t offset, FILE *out) {
  return LOG(out, ou.data(), offset, MDEntryID, MDEntryPx.mantissa, MDEntrySize,
             MDFlags, SecurityID, RptSeq, MDUpdateAction, MDEntryType);
}

int order_book_snapshot::Print(uint64_t offset, FILE *out) {
  return LOG(out, obs.data(), offset, SecurityID, LastMsgSeqNumProcessed,
             RptSeq, ExchangeTradingSessionID, NoMDEntries.blockLength,
             NoMDEntries.numInGroup);
}

int MDEntries::Print(uint64_t offset, FILE *out) {
  return LOG(out, mde.data(), offset, MDEntryID, TransactTime,
             MDEntryPx.mantissa, MDEntrySize, TradeID, MDFlags, MDEntryType);
}

int order_execution::Print(uint64_t offset, FILE *out) {

  return LOG(out, oe.data(), offset, MDEntryID, MDEntryPx.mantissa, MDEntrySize,
             LastPx.mantissa, LastQty, TradeID, MDFlags, SecurityID, RptSeq,
             MDUpdateAction, MDEntryType);
}

int best_prices::Print(uint64_t offset, FILE *out) {
  return LOG(out, bp.data(), offset, MktBidPx.mantissa, MktOfferPx.mantissa,
             BPFlags, SecurityID);
}

int trading_session_status::Print(uint64_t offset, FILE *out) {
  return LOG(out, trading_session.data(), offset, TradSesOpenTime,
             TradSesCloseTime, TradSesIntermClearingStartTime,
             TradSesIntermClearingEndTime, MarketSegmentId,
             ExchangeTradingSessionID, TradSesStatus, MarketId, MarketSegmentId,
             TradSesEvent);
}