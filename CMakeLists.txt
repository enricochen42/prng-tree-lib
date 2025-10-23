cmake_minimum_required(VERSION 3.10)
project(tree_rng_project C)

# uses C11
set(CMAKE_C_STANDARD 11)

# enables AddressSanitizer and debug info
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -g")

# includes directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/CROSS-implementation/Reference_Implementation/include
)

# adds source files
set(SOURCES
    lib/tree_rng.c
    lib/utility_functions.c
    CROSS-implementation/Reference_Implementation/lib/fips202.c
    CROSS-implementation/Reference_Implementation/lib/keccakf1600.c
)

# creates the executable file
add_executable(tree_rng ${SOURCES})

# adds the mathematics library (-lm)
target_link_libraries(tree_rng m)