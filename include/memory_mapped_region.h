#ifndef MEMORY_MAPPED_REGION
#define MEMORY_MAPPED_REGION

#include <cstdint>

class MemoryMappedRegion {
public:
  enum class Mode { READ, WRITE };

  MemoryMappedRegion() = default;
  ~MemoryMappedRegion();

  MemoryMappedRegion(int fd, std::size_t size, uint64_t off);

  void Initialization(int fd, std::size_t sz, uint64_t off, Mode mode);

  uint64_t GetSize() const { return size; }

  char *GetBuffer() { return reinterpret_cast<char *>(memory_buffer); }

  static int GetAlignment();

private:
  void *memory_buffer;
  uint64_t size;
};

#endif