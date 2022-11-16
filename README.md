# Simba

## Building

```
mkdir build
cd build 
cmake ..
```

## Using

```
./simba input.pcap
```


# TODO

1. Support other compilators in cmake (now clang-15 by default)
2. Abstractions for C-code.
3. Refactoring
4. Multithreading - memory pool for every thread (now every thread writes by line in different files - it's very slow)