cmake_minimum_required(VERSION 3.10)
project(libPRNGTreeProjectC)

# use C11
set(CMAKE_C_STANDARD 11)

# define library sources
set(LIB_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/PRNGTree.c
    ${CMAKE_CURRENT_SOURCE_DIR}/utilityFunctions.c
    ${CMAKE_CURRENT_SOURCE_DIR}/CROSS-implementation/Reference_Implementation/lib/fips202.c
    ${CMAKE_CURRENT_SOURCE_DIR}/CROSS-implementation/Reference_Implementation/lib/keccakf1600.c
)

# create the library
add_library(PRNGTreeLib STATIC ${LIB_SOURCES})

# specify include directories for the library
target_include_directories(PRNGTreeLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/CROSS-implementation/Reference_Implementation/include
)

# link math library 
target_link_libraries(PRNGTreeLib PRIVATE m)