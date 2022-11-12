#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>


class MemoryMappedFile
{
public:
    
    explicit MemoryMappedFile(std::string file_name): file_name(file_name), file(0) {}

    bool OpenFileForWrite(std::size_t size);
    bool OpenFileForRead();

    std::size_t GetSize() {
        return memory_buffer_size;
    }

    uint8_t* GetBuffer() {
        return memory_buffer;
    }

    void Sync(uint8_t* end);

private:
    int         file;
    uint8_t    *memory_buffer;
    std::size_t memory_buffer_size;
    std::string file_name;
};




#endif // FILE_H