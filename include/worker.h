#ifndef WORKER_H
#define WORKER_H

#include <string>
#include <vector>

void Worker(int fd, unsigned size, unsigned offset, unsigned diff, unsigned n);

class Preprocessor {
public:
  Preprocessor(std::string file_name);
  void Run();

  auto GetOffsets() { return offsets; }

  auto GetFileSize() {
    return file_size;
  }

private:
  void Calculate();

private:
  std::vector<unsigned> offsets;
  std::string file_name;
  std::size_t file_size;
  unsigned n_threads;
  unsigned chunk_size;
  char *start;
  char *current;
};

#endif // WORKER_H