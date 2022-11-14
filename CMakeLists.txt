cmake_minimum_required(VERSION 3.14)

project(simba)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CPP_COMPILER clang++-15)


find_package(Threads REQUIRED)

set (SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/parser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/tools.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/file.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/memory_mapped_region.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/command_line.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/concurrency.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/worker.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(tests)