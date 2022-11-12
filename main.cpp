#include <fstream>
#include <iostream>
#include "parser.h"
#include "file.h"

int main(int argc, char** argv) {

    std::string file_name(argv[1]);

    MemoryMappedFile m(file_name);

    Parser p;

    p.Parse(m.GetBuffer(), m.GetSize());
    
    return 0;
}