set(MODULE_NAME "cprobeid")
set(MODULE_PATH "${PROJECT_SOURCE_DIR}/probeid")
set(MODULE_SRC_PATH "${MODULE_PATH}/src")
set(MODULE_INCLUDE_PATH "${MODULE_PATH}/src")

find_package(LibXml2 REQUIRED)
find_package(ZLIB REQUIRED)

include_directories(
    ${MODULE_INCLUDE_PATH}
    ${LIBXML2_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${MZXML_READER_LIB_INCLUDE_PATH}
    ${CATCH_INCLUDE_DIR}
)

add_executable(
    cprobeid
    ${MODULE_SRC_PATH}/main.cpp
    ${MODULE_SRC_PATH}/amino_acid.cpp
    ${MODULE_SRC_PATH}/amino_acid_sequence.cpp
    ${MODULE_SRC_PATH}/amino_acid_sequence_fragment.cpp
    ${MODULE_SRC_PATH}/chemical_element.cpp
    ${MODULE_SRC_PATH}/dictionary_amino_acid_modification.cpp
    ${MODULE_SRC_PATH}/dictionary_amino_acid.cpp
    ${MODULE_SRC_PATH}/dictionary.cpp
    ${MODULE_SRC_PATH}/experimental_ion.cpp
    ${MODULE_SRC_PATH}/immonium_ion.cpp
    ${MODULE_SRC_PATH}/ion.cpp
    ${MODULE_SRC_PATH}/msms_run.cpp
    ${MODULE_SRC_PATH}/precursor_ion.cpp
    ${MODULE_SRC_PATH}/protein_database.cpp
    ${MODULE_SRC_PATH}/protein.cpp
    
)

target_link_libraries(cprobeid ${ZLIB_LIBRARIES} ${LIBXML2_LIBRARIES} cln gsl ${Boost_LIBRARIES} ${MZXML_READER_LIB})
