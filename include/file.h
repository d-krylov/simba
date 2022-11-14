#ifndef FILE_H
#define FILE_H

#include <string>

class File {
public:
  explicit File(std::string file_name);
  ~File();

  void Initialization();

  std::size_t GetSize();

  int GetFD() const {
    return file_descriptor;
  }

private:
  int file_descriptor;
  std::size_t size;
  std::string file_name;
};

#endif // FILE_H