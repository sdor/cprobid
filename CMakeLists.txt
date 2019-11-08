cmake_minimum_required(VERSION 3.0.0)
project(cprobid VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
find_package(ZLIB REQUIRED)
find_package(LibXml2 REQUIRED)

include(CTest)
enable_testing()
include_directories (
  ${LIBXML2_INCLUDE_DIRS}
  src
)

file(GLOB SOURCES
  src/*.cpp
  src/*.c
)
add_executable(cprobid ${SOURCES})
target_link_libraries(cprobid ${LIBXML2_LIBRARIES} ${ZLIB_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
