#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

class MemoryMappedFile
{
public:
    
    MemoryMappedFile(std::string file_name) {

        file = open(file_name.c_str(), O_RDONLY);

        if (file < 0) {
            std::cout << "Error" << std::endl;
            abort();
        }

        struct stat s;
        int status = fstat(file, &s);
        memory_buffer_size = s.st_size;

        memory_buffer = reinterpret_cast<uint8_t*>(
            mmap(nullptr, memory_buffer_size, PROT_READ, MAP_PRIVATE, file, 0));
        
        if (memory_buffer == MAP_FAILED) {
            std::cout << "Error memory mapping file!" << std::endl;
            abort();
        }
    }

    std::size_t GetSize() {
        return memory_buffer_size;
    }

    uint8_t* GetBuffer() {
        return memory_buffer;
    }

private:
    int file;
    uint8_t *memory_buffer;
    std::size_t memory_buffer_size;
};




#endif // FILE_H