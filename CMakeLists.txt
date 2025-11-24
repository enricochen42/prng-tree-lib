cmake_minimum_required(VERSION 3.10)
project(PRNGTreeProjectC)

set(CMAKE_C_STANDARD 11)

# include the library directory
add_subdirectory(lib)

# include the tests directory
# uncomment the line below to enable tests
#add_subdirectory(tests) # after compilation: from the project root, run tests with: ./build/tests/testsPRNGTreeC 
