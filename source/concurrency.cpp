#include "concurrency.h"
#include "memory_mapped_region.h"
#include "simba.h"
#include <thread>
#include "worker.h"

Concurrency::Concurrency() { n = std::thread::hardware_concurrency(); }

void Concurrency::Run(int fd, std::vector<unsigned> offsets) {

  std::vector<unsigned> aligned(offsets.size() - 1);
  std::vector<unsigned>   delta(offsets.size() - 1);
  std::vector<unsigned>    size(offsets.size() - 1);

  auto align = MemoryMappedRegion::GetAlignment();

  for (auto i = 0; i < aligned.size(); i++) {
    aligned[i] = offsets[i] & ~(align - 1);
    delta[i] = offsets[i] - aligned[i];
    size[i] = offsets[i+1] - aligned[i];
  }

  std::vector<std::thread> workers(n);

  for (auto i = 0; i < n; i++) {
    workers[i] = std::thread(Worker, fd, size[i], aligned[i], delta[i], i);
  }

  for (auto i = 0; i < n; i++) {
    workers[i].join();
  }
}

