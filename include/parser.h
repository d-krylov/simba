#ifndef PARSER_H
#define PARSER_H

#include <cstdint>

class Parser
{
public:
    
    void Parse(uint8_t* buffer, std::size_t bsize);

private:

    uint8_t* base;

    std::size_t ParseOrderBookSnapshot(uint8_t*& buffer);
    std::size_t ParseOrderUpdate(uint8_t*& buffer);
    std::size_t ParseOrderExecution(uint8_t *&buffer);
    std::size_t ParseTradingSessionStatus(uint8_t *&buffer);
    std::size_t ParseBestPrices(uint8_t *&buffer);
};

#endif // PARSER_H