#include <gtest/gtest.h>
#include "pcap.h"
#include "tools.h"

TEST(GlobalHeaderTest, BasicAssertions) {

    uint8_t buffer[] = {0xd4, 0xc3, 0xb2, 0xa1, 0x02, 0x00, 0x04, 0x00, 
                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                        0xff, 0xff, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00};

    auto hdr = GetGlobalHeader(buffer);

    ASSERT_EQ(hdr->magic_number, 0xa1b2c3d4);
    ASSERT_EQ(hdr->version_major, 0x02);
    ASSERT_EQ(hdr->version_minor, 0x04);
    ASSERT_EQ(hdr->thiszone, 0x000000);
    ASSERT_EQ(hdr->sigfigs, 0x000000);
    ASSERT_EQ(hdr->snaplen, 0x0000ffff);
    ASSERT_EQ(hdr->network, 0x00000001);
}

TEST(PacketHeaderTest, BasicAssertions) {
    uint8_t buffer[] = {0xc0, 0xe8, 0x8b, 0x61, 0x54, 0x00, 0x00, 0x00,
                        0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00};

    auto hdr = GetPacketHeader(buffer);

    ASSERT_EQ(hdr->ts_sec, 0x618be8c0);
    ASSERT_EQ(hdr->ts_usec, 0x00000054);
    ASSERT_EQ(hdr->incl_len, 0x00000078);
    ASSERT_EQ(hdr->orig_len, 0x00000078);
}

TEST(IpTest, BasicAssertions) {
    uint8_t buffer[] = {0x45, 0x00, 0x00, 0x6a, 0x84, 0x7a, 0x40, 0x00, 
                        0x1f, 0x11, 0x79, 0x34, 0x5b, 0xcb, 0xfd, 0xf4, 
                        0xef, 0xc3, 0x14, 0x51};

    auto hdr = GetIp(buffer);

    //ASSERT_EQ(hdr->TotalLength, 0x006a);
}

TEST(UdpTest, BasicAssertions) {
    uint8_t buffer[] = {0xbf, 0x6d, 0x4e, 0x71, 0x00, 0x56, 0xcf, 0xac};

    auto hdr = GetUdp(buffer);

    ASSERT_EQ(SB(hdr->SourcePort), 49005);
    ASSERT_EQ(SB(hdr->DestinationPort), 20081);
    ASSERT_EQ(SB(hdr->Length), 86);
    ASSERT_EQ(SB(hdr->Checksum), 0xcfac);
}
