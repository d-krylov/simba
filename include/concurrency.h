#ifndef CONCURRENCY_H
#define CONCURRENCY_H

#include <vector> 

class Concurrency
{
public:

    Concurrency();
    
    void Run(int fd, std::vector<unsigned> offsets);
    void Preprocessing();

private:
    int n = 0;
};




#endif // CONCURRENCY_H