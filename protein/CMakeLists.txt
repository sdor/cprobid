set(LIB_NAME "protein")
set(MODULE_PATH "${PROJECT_SOURCE_DIR}/${LIB_NAME}")
set(LIB_SRC_PATH "${MODULE_PATH}/src")
set(LIB_INCLUDE_PATH "${MODULE_PATH}/src")
set(CMAKE_CXX_COMPILER ${CMAKE_CXX_COMPILER} CACHE FILEPATH "Compiler")
set(CMAKE_C_COMPILER ${CMAKE_C_COMPILER} CACHE FILEPATH "Compiler")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
include_directories(
    # ${LIBJSON_INCLUDE_DIR}
    ${LIB_INCLUDE_PATH}
    # ${LIBXML2_INCLUDE_DIR}
    ${CATCH_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
)
add_library(
    ${LIB_NAME} SHARED
    src/protein.cpp
    src/AminoAcid.cpp
    src/AminoAcidSeq.cpp
    # src/base64.c
    # src/MzXmlReader.cpp
)

target_link_libraries(
  ${LIB_NAME} 
  # stdc++fs 
  ${ZLIB_LIBRARIES} 
  ${LIBXML2_LIBRARIES}
  ${Boost_LIBRARIES}
)

include(CTest)
add_executable(
  "${LIB_NAME}-test" 
  ${MODULE_PATH}/tests/main.cpp
  ${MODULE_PATH}/tests/test_amino_acid_seq.cpp
)
target_link_libraries("${LIB_NAME}-test" Catch2::Catch ${Boost_LIBRARIES} ${LIB_NAME})

catch_discover_tests(
  "${LIB_NAME}-test"
)

set (PROTEIN_LIB_INCLUDE_PATH  ${LIB_INCLUDE_PATH} PARENT_SCOPE)
set (PROTEIN_LIB ${LIB_NAME} PARENT_SCOPE)