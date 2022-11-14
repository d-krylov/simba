#include "file.h"
#include "memory_mapped_region.h"
#include "command_line.h"
#include "parser.h"
#include "pcap.h"
#include "worker.h"
#include "concurrency.h"
#include <string>
#include <iostream>

void SimpleRun(std::string input_file_name) {
  File in(input_file_name);
  in.Initialization();
  MemoryMappedRegion mm;
  mm.Initialization(in.GetFD(), in.GetSize(), 0, MemoryMappedRegion::Mode::READ);
  Parser p(mm.GetBuffer() + GetGHSize(), mm.GetBuffer() + mm.GetSize());
  p.Parse();
}


int main(int argc, char **argv) {

  CommandLine cli(argc, argv);

  std::string input_file_name(argv[1]);
  
  Preprocessor p(input_file_name);
  p.Run();

  auto offsets = p.GetOffsets();

  offsets.emplace_back(p.GetFileSize());

  Concurrency conc;

  File in(input_file_name);
  in.Initialization();

  conc.Run(in.GetFD(), offsets);

  return 0;
}


