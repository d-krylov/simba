#include "file.h"
#include <fcntl.h>
#include <filesystem>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

File::File(std::string file_name) : file_name(file_name), size(0) {}

void File::Initialization() {

  file_descriptor = open(file_name.c_str(), O_CREAT | O_RDWR);

  if (file_descriptor == -1) {
  }
}

std::size_t File::GetSize() {
  if (size != 0) {
    return size;
  }
  size = std::filesystem::file_size(file_name);
  return size;
}

File::~File() {
  if (file_descriptor) {
    close(file_descriptor);
  }
}