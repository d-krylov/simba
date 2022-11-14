#include "memory_mapped_region.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

MemoryMappedRegion::MemoryMappedRegion(int fd, std::size_t sz, uint64_t off)
    : size(sz) {}

MemoryMappedRegion::~MemoryMappedRegion() {
  if (memory_buffer) {
    munmap(memory_buffer, size);
  }
}

int MemoryMappedRegion::GetAlignment() { return sysconf(_SC_PAGE_SIZE); }

void MemoryMappedRegion::Initialization(int fd, std::size_t sz, uint64_t off,
                                        Mode mode) {

  auto flags = (mode == Mode::WRITE) ? MAP_SHARED : MAP_PRIVATE;
  auto prot = (mode == Mode::READ) ? PROT_READ : (PROT_READ | PROT_WRITE);

  memory_buffer = mmap(nullptr, sz, prot, flags, fd, off);

  if (memory_buffer == MAP_FAILED) {
  }
}