#include "worker.h"
#include "file.h"
#include "memory_mapped_region.h"
#include "pcap.h"
#include "tools.h"
#include "parser.h"
#include <filesystem>
#include <thread>
#include <iostream>

void Worker(int fd, unsigned size, unsigned offset, unsigned diff, unsigned n) {

  MemoryMappedRegion input;
  
  input.Initialization(fd, size, offset, MemoryMappedRegion::Mode::READ);

  Parser p(input.GetBuffer() + diff, input.GetBuffer() + size);

  p.Parse();
}


Preprocessor::Preprocessor(std::string file_name) {
  this->file_name = file_name;
  file_size = std::filesystem::file_size(file_name);
  n_threads = std::thread::hardware_concurrency();
  chunk_size = file_size / n_threads;
}

void Preprocessor::Run() {

  File in(file_name);
  in.Initialization();
  MemoryMappedRegion mm;
  mm.Initialization(in.GetFD(), in.GetSize(), 0, MemoryMappedRegion::Mode::READ);
  start = mm.GetBuffer();
  current = mm.GetBuffer();
  Calculate();
}

void Preprocessor::Calculate() {

  ip_header *ip;
  std::size_t chunk_current_size = 0;

  unsigned i = 0;

  offsets.emplace_back(0);
  current += GetGHSize();

  while (i < n_threads - 1) {

    current += GetPHSize();
    current += GetETHSize();

    ip = GetIp(current);
    auto sz = SB(ip->TotalLength);

    current += sz;
    chunk_current_size += sz;

    if (chunk_current_size >= chunk_size) {
      offsets.emplace_back(current - start);
      chunk_current_size = 0;
      i++;
    }
  }
}