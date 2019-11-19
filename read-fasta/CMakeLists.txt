set(MODULE_NAME "protein")
set(MODULE_PATH "${PROJECT_SOURCE_DIR}/${MODULE_NAME}")
set(MODULE_SRC_PATH "${MODULE_PATH}/src")
set(MODULE_INCLUDE_PATH "${MODULE_PATH}/src")

include_directories(
    ${MODULE_INCLUDE_PATH}
    ${CATCH_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
)

add_executable(
    read-fasta
    src/main.cpp
)

# target_link_libraries(
#   # stdc++fs 
#   ${ZLIB_LIBRARIES} 
#   ${LIBXML2_LIBRARIES}
#   ${Boost_LIBRARIES}
# )

# include(CTest)
# add_executable(
#   "${LIB_NAME}-test" 
#   ${MODULE_PATH}/tests/main.cpp
#   ${MODULE_PATH}/tests/test_amino_acid_seq.cpp
# )
# target_link_libraries("${LIB_NAME}-test" Catch2::Catch ${Boost_LIBRARIES} ${LIB_NAME})

# catch_discover_tests(
#   "${LIB_NAME}-test"
# )

# set (PROTEIN_LIB_INCLUDE_PATH  ${LIB_INCLUDE_PATH} PARENT_SCOPE)
# set (PROTEIN_LIB ${LIB_NAME} PARENT_SCOPE)