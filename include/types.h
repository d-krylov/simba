#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

#define PACKED __attribute__((packed))

struct group_size
{
    uint16_t blockLength;
    uint8_t numInGroup;
} PACKED;

struct Decimal5
{
    uint64_t mantissa;
};

struct Decimal5NULL
{
    uint64_t mantissa;
};

struct String25
{
    /* data */
};

enum TemplateID {
  Heartbeat = 1,
  SequenceReset,
  BestPrices,
  EmptyBook = 4,
  OrderUpdate = 5,
  OrderExecution = 6,
  OrderBookSnapshot = 7,
  SecurityDefinition = 8,
  SecurityStatus = 9,
  SecurityDefinitionUpdateReport = 10,
  TradingSessionStatus = 11
};


#endif // TYPES_H
