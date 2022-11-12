#ifndef PARSER_H
#define PARSER_H

#include <cstdint>
 

class Parser
{
public:
    
    void Parse(uint8_t* buffer, char* out, std::size_t bsize);

    void GetPacketsOffset(uint8_t* buffer);

    uint8_t* GetEnd() {
        return reinterpret_cast<uint8_t*>(out);
    }

private:

    uint8_t* base;
    char*    out;

    int out_offset = 0;

    std::size_t ParseOrderBookSnapshot(uint8_t*& buffer, char*& out);
    std::size_t ParseOrderUpdate(uint8_t*& buffer, char*& out);
    std::size_t ParseOrderExecution(uint8_t *&buffer, char*& out);
    std::size_t ParseTradingSessionStatus(uint8_t *&buffer, char*& out);
    std::size_t ParseBestPrices(uint8_t *&buffer, char*& out);
};

#endif // PARSER_H