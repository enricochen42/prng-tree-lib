cmake_minimum_required(VERSION 3.10)
project(PRNGTreeProjectC)

set(CMAKE_C_STANDARD 11)

# include the library directory
add_subdirectory(lib)

# include the tests directory
add_subdirectory(tests) # Comment this line to disable tests