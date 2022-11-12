#include "file.h"
#include "parser.h"
#include <fstream>
#include <iostream>
#include "tools.h"

void Help(void) {
  std::cout << "Using: ./simba input-file output-file" << std::endl;
}

int main(int argc, char **argv) {

  if (argc == 1) {
    Help();
    return 0;
  }

  std::string input_file_name(argv[1]);
  std::string output_file_name;

  if (argc > 2) {
    output_file_name = argv[2];
  }

  MemoryMappedFile in(input_file_name);
  MemoryMappedFile out(output_file_name); 
  
  in.OpenFileForRead();
  out.OpenFileForWrite(GetOutputSize(in.GetSize()));

  Parser p;

  p.Parse(in.GetBuffer(), reinterpret_cast<char*>(out.GetBuffer()), in.GetSize());

  out.Sync(p.GetEnd());

  return 0;
}