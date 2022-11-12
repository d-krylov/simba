#include "file.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

bool MemoryMappedFile::OpenFileForRead() {

  if (file != 0)
    return false;

  file = open(file_name.c_str(), O_RDONLY);

  if (file < 0) {
    std::cout << "Error" << std::endl;
    abort();
  }

  struct stat s;
  int status = fstat(file, &s);
  memory_buffer_size = s.st_size;

  memory_buffer = reinterpret_cast<uint8_t *>(
      mmap(nullptr, memory_buffer_size, PROT_READ, MAP_PRIVATE, file, 0));

  if (memory_buffer == MAP_FAILED) {
    close(file);
    perror("Error mmapping the file");
    exit(EXIT_FAILURE);
  }

  return true;
}

bool MemoryMappedFile::OpenFileForWrite(std::size_t size) {

  if (file != 0)
    return false;

  file = open(file_name.c_str(), O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);

  if (file < 0) {
    std::cout << "Error" << std::endl;
    abort();
  }

  if (lseek(file, size - 1, SEEK_SET) == -1) {
    close(file);
    perror("Error calling lseek() to 'stretch' the file");
    exit(EXIT_FAILURE);
  }

  if (write(file, "", 1) == -1) {
    close(file);
    perror("Error writing last byte of the file");
    exit(EXIT_FAILURE);
  }

  memory_buffer = reinterpret_cast<uint8_t *>(
      mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, file, 0));

  if (memory_buffer == MAP_FAILED) {
    close(file);
    perror("Error mmapping the file");
    exit(EXIT_FAILURE);
  }

  return true;
}

void MemoryMappedFile::Sync(uint8_t *end) {

  std::cout << "Writing " << end - memory_buffer << std::endl;

  if (msync(memory_buffer, end - memory_buffer, MS_SYNC) == -1) {
    perror("Could not sync the file to disk");
  }

  if (munmap(memory_buffer, memory_buffer_size) == -1) {
    close(file);
    perror("Error un-mmapping the file");
    exit(EXIT_FAILURE);
  }

  close(file);
}