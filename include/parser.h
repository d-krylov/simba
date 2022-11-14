#ifndef PARSER_H
#define PARSER_H

#include "global.h"
#include <cstdint>
#include <vector>
#include <stdio.h>

class Parser {
public:
  Parser(char *l, char *r, FILE* out = nullptr);

  void Parse();

  std::size_t GetOffset() { return (current - start); }

private:
  char *start;
  char *end;
  char *current;
  FILE *out;

private:
  std::size_t ParseGlobalHeader();
  std::size_t ParseOrderBookSnapshot();
  std::size_t ParseOrderUpdate();
  std::size_t ParseOrderExecution();
  std::size_t ParseTradingSessionStatus();
  std::size_t ParseBestPrices();
};

#endif // PARSER_H