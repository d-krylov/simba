#ifndef TOOLS_H
#define TOOLS_H

#include <cstdint>
#include <string_view>
#include <string>
#include "pcap.h"
#include "simba.h"

inline uint16_t SB(uint16_t v) {
    return (v << 8) | (v >> 8);
}



void PrintGlobalHeader(global_header& h, uint64_t offset); 
void PrintPacketHeader(packet_header& h, uint64_t offset);
void PrintUdp(udp& h, uint64_t offset);
void PrintMarketDataPacketHeader(market_data_packet_header& h, uint64_t offset);
void PrintIncrementalPacketHeader(incremental_packet_header& h, uint64_t offset);
void PrintSbeHeader(sbe_header& h, uint64_t offset);
void PrintOrderUpdate(order_update& h, uint64_t offset);
void PrintOrderExecution(order_execution& h, uint64_t offset);
void PrintOrderBookSnapshot(order_book_snapshot& h, uint64_t offset);
void PrintMDEntry(MDEntries& h, uint64_t offset);
void PrintBestPrices(best_prices& h, uint64_t offset);
void PrintTradingSessionStatus(trading_session_status& h, uint64_t offset);






#endif // TOOLS_H