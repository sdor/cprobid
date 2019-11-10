set(LIB_NAME "mzxml-reader")
set(MODULE_PATH "${PROJECT_SOURCE_DIR}/mzxml-reader")
set(LIB_SRC_PATH "${MODULE_PATH}/src")
set(LIB_INCLUDE_PATH "${MODULE_PATH}/src")

include_directories(
    ${LIBJSON_INCLUDE_DIR}
    ${LIB_INCLUDE_PATH}
    ${LIBXML2_INCLUDE_DIR}
    ${CATCH_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
)
add_library(
    mzxml-reader SHARED
    src/base64.c
    src/MzXmlReader.cpp
)

target_link_libraries(
  mzxml-reader 
  # stdc++fs 
  ${ZLIB_LIBRARIES} 
  ${LIBXML2_LIBRARIES}
  ${Boost_LIBRARIES}
)

include(CTest)
add_executable(
  mzxml-reader-test 
  ${MODULE_PATH}/tests/main.cpp
  ${MODULE_PATH}/tests/test_read.cpp
)
target_link_libraries(mzxml-reader-test Catch2::Catch ${Boost_LIBRARIES} mzxml-reader)

catch_discover_tests(
  mzxml-reader-test
)

set (MZXML_READER_LIB_INCLUDE_PATH  ${LIB_INCLUDE_PATH} PARENT_SCOPE)
set (MZXML_READER_LIB ${LIB_NAME} PARENT_SCOPE)