cmake_minimum_required(VERSION 3.0.0)
project(cprobid VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CTest)
include(Catch)

enable_testing()

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch)

add_library(Catch2::Catch IMPORTED INTERFACE)


find_package(LibXml2 REQUIRED)
find_package(ZLIB REQUIRED)
find_package(
    Boost
    REQUIRED
    COMPONENTS iostreams program_options system filesystem
)

# add_subdirectory(genebank)
# add_subdirectory(pubmed)
# add_subdirectory(unpack-pubmed)
# add_subdirectory(link-pubmed)
# add_subdirectory(plot-pubmed-links-hist)
# add_subdirectory(pubmed-db)
# add_subdirectory(pubmed-utils)
# add_subdirectory(read-pubmed)
# add_subdirectory(pubmed-persists)
add_subdirectory(mzxml-reader)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

