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




#endif // TOOLS_H