set(MODULE_NAME "read-swissprot")
set(MODULE_PATH "${PROJECT_SOURCE_DIR}/${MODULE_NAME}")
set(MODULE_SRC_PATH "${MODULE_PATH}/src")
set(MODULE_INCLUDE_PATH "${MODULE_PATH}/src")

include_directories(
    ${MODULE_INCLUDE_PATH}
    ${CATCH_INCLUDE_DIR}
    ${LIBXML2_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
    ${PROTEIN_LIB_INCLUDE_PATH}
    ${SWISSPROT_LIB_INCLUDE_PATH}
)

add_executable(
    read-swissprot
    src/main.cpp
)

target_link_libraries(
  read-swissprot  
  ${ZLIB_LIBRARIES} 
  ${LIBXML2_LIBRARIES}
  ${Boost_LIBRARIES}
  ${SWISSPROT_LIB}
  ${PROTEIN_LIB} 
)