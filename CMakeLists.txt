cmake_minimum_required(VERSION 3.23)

project(LinAlg)

add_library(LinAlg)

target_sources(LinAlg
  PRIVATE
    src/Vector.cc
    src/Matrix.cc

  PUBLIC
    FILE_SET myHeaders
    TYPE HEADERS
    BASE_DIRS
      include
    FILES
      include/tinyeigen/Vector.h
      include/tinyeigen/Matrix.h

)

target_include_directories(LinAlg
  PUBLIC
    include
)

enable_testing()

add_executable(vector_tests tests/vector_tests.cc)
add_executable(matrix_tests tests/matrix_tests.cc)
target_link_libraries(vector_tests PRIVATE LinAlg)
target_link_libraries(matrix_tests PRIVATE LinAlg)
add_test(NAME vector_tests COMMAND vector_tests)
add_test(NAME matrix_tests COMMAND matrix_tests)