cmake_minimum_required(VERSION 3.23)

project(LinAlg)

add_library(LinAlg)

target_sources(LinAlg
  PRIVATE
    library_implementation.cc

  PUBLIC
    FILE_SET myHeaders
    TYPE HEADERS
    BASE_DIRS
      include
    FILES
      include/header.h

)