set(LIB_NAME "swissprot")
set(MODULE_PATH "${PROJECT_SOURCE_DIR}/${LIB_NAME}")
set(LIB_SRC_PATH "${MODULE_PATH}/src")
set(LIB_INCLUDE_PATH "${MODULE_PATH}/src")
# find_package(libbsoncxx 3.4.0 REQUIRED)
find_package(libmongocxx REQUIRED)
message( "LIBS: ${LIBBSONCXX_LIBRARIES}" )
include_directories(
    ${LIB_INCLUDE_PATH}
    ${LIBBSONCXX_INCLUDE_DIRS}
    ${LIBMONGOCXX_INCLUDE_DIRS}
    ${PROTEIN_LIB_INCLUDE_PATH}
    ${MSMS_LIB_INCLUDE_PATH}
    ${LIBXML2_INCLUDE_DIR}
    ${CATCH_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
)
add_library(
    ${LIB_NAME} SHARED
    src/reader.cpp
    src/parser.cpp
)

target_link_libraries(
  ${LIB_NAME} 
  ${ZLIB_LIBRARIES} 
  ${LIBXML2_LIBRARIES}
  ${Boost_LIBRARIES}
)

add_executable(
  digest-swissprot
  src/digest-swissprot.cpp
)

target_link_libraries(
  digest-swissprot
  ${LIB_NAME}
  ${PROTEIN_LIB} 
  ${MSMS_LIB}
  ${LIBMONGOCXX_LIBRARIES} 
  ${ZLIB_LIBRARIES} 
  ${LIBXML2_LIBRARIES}
)

include(CTest)
enable_testing()
add_executable(
  "${LIB_NAME}-test" 
  ${MODULE_PATH}/tests/main.cpp
  ${MODULE_PATH}/tests/test_parser.cpp
)
target_link_libraries("${LIB_NAME}-test" Catch2::Catch ${Boost_LIBRARIES} ${LIB_NAME})

catch_discover_tests(
  "${LIB_NAME}-test"
)

set (SWISSPROT_LIB_INCLUDE_PATH  ${LIB_INCLUDE_PATH} PARENT_SCOPE)
set (SWISSPROT_LIB ${LIB_NAME} PARENT_SCOPE)