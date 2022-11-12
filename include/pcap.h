#ifndef PCAP_H
#define PCAP_H

#include <cstdint>

struct global_header {
  uint32_t magic_number;
  uint16_t version_major;
  uint16_t version_minor;
  int32_t thiszone;
  uint32_t sigfigs;
  uint32_t snaplen;
  uint32_t network;
};

struct packet_header {
  uint32_t ts_sec;
  uint32_t ts_usec;
  uint32_t incl_len;
  uint32_t orig_len;
};

struct ip {
  uint8_t Version_IHL;
  uint8_t DSCP_ECN;
  uint16_t TotalLength;
  uint16_t Identification;
  uint16_t Flags_FragmentOffset;
  uint8_t TimeToLive;
  uint8_t Protocol;
  uint8_t HeaderChecksum;
  uint32_t SourceIPAddress;
  uint32_t DestinationIPAddress;
};

struct ethernet {
  uint8_t data[14];
};

struct udp {
  uint16_t SourcePort;
  uint16_t DestinationPort;
  uint16_t Length;
  uint16_t Checksum;
};

inline global_header *GetGlobalHeader(uint8_t *ptr) {
  return reinterpret_cast<global_header *>(ptr);
}

inline packet_header *GetPacketHeader(uint8_t *ptr) {
  return reinterpret_cast<packet_header *>(ptr);
}

inline ip *GetIp(uint8_t *ptr) { return reinterpret_cast<ip *>(ptr); }

inline udp *GetUdp(uint8_t *ptr) { return reinterpret_cast<udp *>(ptr); }

#endif // PCAP_H