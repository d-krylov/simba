#include "parser.h"
#include "pcap.h"
#include "print_strings.h"
#include "simba.h"
#include "tools.h"
#include <cassert>
#include <iostream>
#include <thread>

Parser::Parser(char *l, char *r) : start(l), end(r) {}

void Parser::Parse() {

  std::size_t i = 0;

  current = start;

  while (current != end) {

    auto ph = GetPacketHeader(current);

    ph->Print(GetOffset(), out);

    current += GetPHSize();
    current += GetIPSize() + GetETHSize();
    auto uph = GetUdp(current);

    uph->Print(GetOffset(), out);

    current += GetUDPSize();

    auto mdph = GetMarketDataPacketHeader(current);
    int message_size = mdph->MsgSize;

    mdph->Print(GetOffset(), out);

    current += GetMDPHSize();
    message_size -= GetMDPHSize();

    if (mdph->MsgFlags & FLAG_INCREMENTAL) {

      auto iph = GetIncrementalPacketHeader(current);
      iph->Print(GetOffset(), out);

      current += GetIPHSize();
      message_size -= GetIPHSize();
    }

    while (message_size > 0) {
      auto sbeh = GetSbeHeader(current);

      sbeh->Print(GetOffset(), out);

      current += GetSBESize();
      message_size -= GetSBESize();

      switch (sbeh->TemplateID) {
      case TemplateID::OrderUpdate:
        message_size -= ParseOrderUpdate();
        break;
      case TemplateID::OrderBookSnapshot:
        message_size -= ParseOrderBookSnapshot();
        break;
      case TemplateID::OrderExecution:
        message_size -= ParseOrderExecution();
        break;
      case TemplateID::SecurityDefinition:
        current += message_size;
        message_size = 0;
        break;
      case TemplateID::BestPrices:
        message_size -= ParseBestPrices();
        break;
      case TemplateID::TradingSessionStatus:
        current += message_size;
        message_size = 0;
        break;
      case TemplateID::SequenceReset:
        message_size -= sizeof(SequenceReset);
        current += sizeof(SequenceReset);
        break;
      case TemplateID::Heartbeat:
        break;
      case TemplateID::SecurityDefinitionUpdateReport:
        current += message_size;
        message_size = 0;
        break;
      case TemplateID::EmptyBook:
        current += message_size;
        message_size = 0;
        break;
      case TemplateID::SecurityStatus:
        current += message_size;
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

std::size_t Parser::ParseGlobalHeader() {
  auto gh = GetGlobalHeader(current);
  gh->Print(GetOffset(), out);

  current += GetGHSize();
}

std::size_t Parser::ParseOrderBookSnapshot() {
  std::size_t size = 0;
  auto obsn = GetOrderBookSnapshot(current);
  obsn->Print(GetOffset(), out);

  current += GetOBSSize();
  size += GetOBSSize();

  for (uint8_t j = 0; j < obsn->NoMDEntries.numInGroup; j++) {
    auto mde = GetMDEntries(current);
    mde->Print(GetOffset(), out);
    current += sizeof(MDEntries);
    size += sizeof(MDEntries);
  }
  return size;
}

std::size_t Parser::ParseOrderExecution() {
  auto oe = GetOrderExecution(current);
  oe->Print(GetOffset(), out);
  current += sizeof(order_execution);
  return sizeof(order_execution);
}

std::size_t Parser::ParseOrderUpdate() {
  auto ouh = GetOrderUpdate(current);
  ouh->Print(GetOffset(), out);
  current += GetOUSize();
  return GetOUSize();
}

std::size_t Parser::ParseTradingSessionStatus() {
  auto tss = GetTradingSessionStatus(current);
  tss->Print(GetOffset(), out);
  return GetTSSSize();
}

std::size_t Parser::ParseBestPrices() {
  std::size_t size = 0;
  auto gs = GetGroupSize(current);
  current += sizeof(group_size);
  size += sizeof(group_size);

  for (int j = 0; j < gs->numInGroup; j++) {
    auto bp = GetBestPrices(current);
    bp->Print(GetOffset(), out);
    current += sizeof(best_prices);
    size += sizeof(best_prices);
  }
  return size;
}