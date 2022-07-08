project(hip_tests LANGUAGES CXX)
cmake_minimum_required(VERSION 3.13)

include(ExternalProject)
ExternalProject_Add(gtest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz
  URL_MD5 e82199374acdfda3f425331028eb4e2a

  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
  INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/gtest_install 
  # don't know why it is not installing into the default as given in documentation
  CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/gtest_install
)
ExternalProject_Get_Property(gtest source_dir binary_dir install_dir)

add_executable( hip_tests main.cpp )
add_dependencies(hip_tests gtest)
target_include_directories(hip_tests PUBLIC ${PROJECT_SOURCE_DIR}/common)
target_include_directories(hip_tests PUBLIC ${install_dir}/include)
target_compile_options(hip_tests PUBLIC -O0 -Wall -Wextra -Wpedantic -Werror)
target_link_libraries(hip_tests ${binary_dir}/lib/libgtest.a)
target_link_libraries(hip_tests ${binary_dir}/lib/libgtest_main.a)

enable_testing()
add_test (NAME hip_tests COMMAND hip_tests)

