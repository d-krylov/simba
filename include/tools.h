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

inline std::size_t GetOutputSize(std::size_t in) {
    return in * 6;
}

int PrintGlobalHeader(global_header& h, uint64_t offset, char* out); 
int PrintPacketHeader(packet_header& h, uint64_t offset, char* out);
int PrintUdp(udp& h, uint64_t offset, char* out);
int PrintMarketDataPacketHeader(market_data_packet_header& h, uint64_t offset, char* out);
int PrintIncrementalPacketHeader(incremental_packet_header& h, uint64_t offset, char* out);
int PrintSbeHeader(sbe_header& h, uint64_t offset, char* out);
int PrintOrderUpdate(order_update& h, uint64_t offset, char* out);
int PrintOrderExecution(order_execution& h, uint64_t offset, char* out);
int PrintOrderBookSnapshot(order_book_snapshot& h, uint64_t offset, char* out);
int PrintMDEntry(MDEntries& h, uint64_t offset, char* out);
int PrintBestPrices(best_prices& h, uint64_t offset, char* out);
int PrintTradingSessionStatus(trading_session_status& h, uint64_t offset, char* out);






#endif // TOOLS_H