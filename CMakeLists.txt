cmake_minimum_required(VERSION 3.10)
project(PRNGTreeProjectC)

set(CMAKE_C_STANDARD 11)

# include the library directory
add_subdirectory(lib)

# include the tests directory
# uncomment the line below to enable tests
# add_subdirectory(tests) 
# remember to use shakeStub instead of shake256 inside RNG function from lib/utilityFunctions.c
# after compilation: from the library root, run tests with: ./build/tests/testsPRNGTreeC 