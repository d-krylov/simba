include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(pcap_test pcap_test.cpp)
add_executable(simba_test simba_test.cpp)

target_include_directories(pcap_test PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(pcap_test PRIVATE GTest::GTest)

target_include_directories(simba_test PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(simba_test PRIVATE GTest::GTest)

add_test(pcap_gtest pcap_test)
add_test(simba_gtest simba_test)