cmake_minimum_required(VERSION 3.23)

project(LinAlg)

add_library(LinAlg)

target_sources(LinAlg
  PRIVATE
    src/Vector.cc

  PUBLIC
    FILE_SET myHeaders
    TYPE HEADERS
    BASE_DIRS
      include
    FILES
      include/tinyeigen/Vector.h

)

target_include_directories(LinAlg
  PUBLIC
    include
)

enable_testing()

add_executable(vector_tests tests/vector_tests.cc)
target_link_libraries(vector_tests PRIVATE LinAlg)
add_test(NAME vector_tests COMMAND vector_tests)