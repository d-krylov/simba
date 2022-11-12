#include "parser.h"
#include "pcap.h"
#include "print_strings.h"
#include "simba.h"
#include "tools.h"
#include <cassert>
#include <iostream>

void Parser::GetPacketsOffset(uint8_t* buffer) {


}

void Parser::Parse(uint8_t *buffer, char *out, std::size_t bsize) {

  base = buffer;

  auto gh = GetGlobalHeader(buffer);
  out_offset = PrintGlobalHeader(*gh, buffer - base, out);
  
  buffer += sizeof(global_header);
  out += out_offset;

  std::size_t i = 0;

  while (buffer != base + bsize) {

    auto ph = GetPacketHeader(buffer);
    std::cout << "Packet number " << i++ << std::endl;
    out_offset = PrintPacketHeader(*ph, buffer - base, out);
    out += out_offset;
    buffer += sizeof(packet_header);
    buffer += sizeof(ip) + sizeof(ethernet);
    auto uph = GetUdp(buffer);

    out_offset = PrintUdp(*uph, buffer - base, out);
    
    out += out_offset;
    buffer += sizeof(udp);

    auto mdph = GetMarketDataPacketHeader(buffer);
    int message_size = mdph->MsgSize;

    out_offset = PrintMarketDataPacketHeader(*mdph, buffer - base, out);

    out += out_offset;
    buffer += sizeof(market_data_packet_header);
    message_size -= sizeof(market_data_packet_header);

    if (mdph->MsgFlags & FLAG_INCREMENTAL) {

      auto iph = GetIncrementalPacketHeader(buffer);
      out_offset = PrintIncrementalPacketHeader(*iph, buffer - base, out);

      out += out_offset;
      buffer += sizeof(incremental_packet_header);
      message_size -= sizeof(incremental_packet_header);
    }

    while (message_size > 0) {
      auto sbeh = GetSbeHeader(buffer);

      out_offset = PrintSbeHeader(*sbeh, buffer - base, out);

      out += out_offset;
      buffer += sizeof(sbe_header);
      message_size -= sizeof(sbe_header);

      switch (sbeh->TemplateID) {
      case TemplateID::OrderUpdate:
        message_size -= ParseOrderUpdate(buffer, out);
        break;
      case TemplateID::OrderBookSnapshot:
        message_size -= ParseOrderBookSnapshot(buffer, out);
        break;
      case TemplateID::OrderExecution:
        message_size -= ParseOrderExecution(buffer, out);
        break;
      case TemplateID::SecurityDefinition:
        buffer += message_size;
        message_size = 0;
        break;
      case TemplateID::BestPrices:
        message_size -= ParseBestPrices(buffer, out);
        break;
      case TemplateID::TradingSessionStatus:
        buffer += message_size;
        message_size = 0;
        break;
      case TemplateID::SequenceReset:
        message_size -= sizeof(SequenceReset);
        buffer += sizeof(SequenceReset);
        break;
      case TemplateID::Heartbeat:
        break;
      case TemplateID::SecurityDefinitionUpdateReport:
        buffer += message_size;
        message_size = 0;
        break;
      case TemplateID::EmptyBook:
        buffer += message_size;
        message_size = 0;
        break;
      case TemplateID::SecurityStatus:
        buffer += message_size;
        message_size = 0;
        break;
      default:
        std::cout << "oops"
                  << " " << sbeh->TemplateID << std::endl;
        return;
        break;
      }
    }
    assert(message_size == 0);
  }
}

std::size_t Parser::ParseOrderBookSnapshot(uint8_t *&buffer, char*& out) {
  std::size_t size = 0;
  auto obsn = GetOrderBookSnapshot(buffer);
  out_offset = PrintOrderBookSnapshot(*obsn, buffer - base, out);

  out += out_offset;
  buffer += sizeof(order_book_snapshot);
  size += sizeof(order_book_snapshot);

  for (uint8_t j = 0; j < obsn->NoMDEntries.numInGroup; j++) {
    auto mde = GetMDEntries(buffer);
    out_offset = PrintMDEntry(*mde, buffer - base, out);
    out += out_offset;
    buffer += sizeof(MDEntries);
    size += sizeof(MDEntries);
  }
  return size;
}

std::size_t Parser::ParseOrderExecution(uint8_t *&buffer, char*& out) {
  auto oe = GetOrderExecution(buffer);
  out_offset = PrintOrderExecution(*oe, buffer - base, out);
  out += out_offset;
  buffer += sizeof(order_execution);
  return sizeof(order_execution);
}

std::size_t Parser::ParseOrderUpdate(uint8_t *&buffer, char*& out) {
  auto ouh = GetOrderUpdate(buffer);
  out_offset = PrintOrderUpdate(*ouh, buffer - base, out);
  out += out_offset;
  buffer += sizeof(order_update);
  return sizeof(order_update);
}

std::size_t Parser::ParseTradingSessionStatus(uint8_t *&buffer, char*& out) {
  auto tss = GetTradingSessionStatus(buffer);
  out_offset = PrintTradingSessionStatus(*tss, buffer - base, out);
  out += out_offset;
  return sizeof(trading_session_status);
}

std::size_t Parser::ParseBestPrices(uint8_t *&buffer, char*& out) {
  std::size_t size = 0;
  auto gs = GetGroupSize(buffer);
  buffer += sizeof(group_size);
  size += sizeof(group_size);

  for (int j = 0; j < gs->numInGroup; j++) {
    auto bp = GetBestPrices(buffer);
    out_offset = PrintBestPrices(*bp, buffer - base, out);
    out += out_offset;
    buffer += sizeof(best_prices);
    size += sizeof(best_prices);
  }
  return size;
}