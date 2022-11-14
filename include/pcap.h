#ifndef PCAP_H
#define PCAP_H

#include "simba_types.h"

struct global_header {
  uint32_t magic_number;
  uint16_t version_major;
  uint16_t version_minor;
  int32_t thiszone;
  uint32_t sigfigs;
  uint32_t snaplen;
  uint32_t network;
  int Print(uint64_t offset, FILE *out);
} PACKED;

struct packet_header {
  uint32_t ts_sec;
  uint32_t ts_usec;
  uint32_t incl_len;
  uint32_t orig_len;
  int Print(uint64_t offset, FILE *out);
} PACKED;

struct ip_header {
  uint8_t Version_IHL;
  uint8_t DSCP_ECN;
  uint16_t TotalLength;
  uint16_t Identification;
  uint16_t Flags_FragmentOffset;
  uint8_t TimeToLive;
  uint8_t Protocol;
  uint16_t HeaderChecksum;
  uint32_t SourceIPAddress;
  uint32_t DestinationIPAddress;
  int Print(uint64_t offset, FILE *out);
} PACKED;

struct ethernet_header {
  uint8_t data[14];
} PACKED;

struct udp_header {
  uint16_t SourcePort;
  uint16_t DestinationPort;
  uint16_t Length;
  uint16_t Checksum;
  int Print(uint64_t offset, FILE *out);
} PACKED;

inline global_header *GetGlobalHeader(char *ptr) {
  return reinterpret_cast<global_header *>(ptr);
}

inline packet_header *GetPacketHeader(char *ptr) {
  return reinterpret_cast<packet_header *>(ptr);
}

inline std::size_t GetGHSize() {
  return sizeof(global_header);
}

inline std::size_t GetPHSize() {
  return sizeof(packet_header);
}

inline std::size_t GetETHSize() {
  return sizeof(ethernet_header);
}

inline constexpr std::size_t GetUDPSize() {
  return sizeof(udp_header);
}

inline constexpr std::size_t GetIPSize() {
  return sizeof(ip_header);
}

inline ip_header *GetIp(char *ptr) { return reinterpret_cast<ip_header *>(ptr); }

inline udp_header *GetUdp(char *ptr) { return reinterpret_cast<udp_header *>(ptr); }


static_assert(GetIPSize() == 20);
static_assert(GetUDPSize() == 8);

#endif // PCAP_H