cmake_minimum_required(VERSION 3.23)

project(LinAlg
  VERSION 0.1.0
  DESCRIPTION "A tiny linear-algebra library for vectors and matrices"
  HOMEPAGE_URL "https://github.com/joepdejong/LinAlg"
  LANGUAGES CXX
)

# ── C++ standard ──────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Library target ────────────────────────────────────────────────────────────
add_library(tinyeigen)
add_library(tinyeigen::tinyeigen ALIAS tinyeigen)

target_sources(tinyeigen
  PRIVATE
    src/Vector.cc
    src/Matrix.cc
  PUBLIC
    FILE_SET tinyeigen_headers
    TYPE HEADERS
    BASE_DIRS include
    FILES
      include/tinyeigen/Vector.h
      include/tinyeigen/Matrix.h
)

target_include_directories(tinyeigen
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# ── Install rules ─────────────────────────────────────────────────────────────
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS tinyeigen
  EXPORT tinyeigenTargets
  LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  FILE_SET tinyeigen_headers
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT tinyeigenTargets
  FILE        tinyeigenTargets.cmake
  NAMESPACE   tinyeigen::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tinyeigen
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/tinyeigenConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/tinyeigenConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/tinyeigenConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tinyeigen
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/tinyeigenConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/tinyeigenConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tinyeigen
)

# ── Tests ─────────────────────────────────────────────────────────────────────
option(TINYEIGEN_BUILD_TESTS "Build unit tests" ON)

if(TINYEIGEN_BUILD_TESTS)
  enable_testing()

  add_executable(vector_tests tests/vector_tests.cc)
  add_executable(matrix_tests tests/matrix_tests.cc)

  target_link_libraries(vector_tests PRIVATE tinyeigen)
  target_link_libraries(matrix_tests PRIVATE tinyeigen)

  add_test(NAME vector_tests COMMAND vector_tests)
  add_test(NAME matrix_tests COMMAND matrix_tests)
endif()