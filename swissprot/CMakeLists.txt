set(LIB_NAME "swissprot")
set(MODULE_PATH "${PROJECT_SOURCE_DIR}/${LIB_NAME}")
set(LIB_SRC_PATH "${MODULE_PATH}/src")
set(LIB_INCLUDE_PATH "${MODULE_PATH}/src")
include_directories(
    # ${LIBJSON_INCLUDE_DIR}
    ${LIB_INCLUDE_PATH}
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

include(CTest)
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