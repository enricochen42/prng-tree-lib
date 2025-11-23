cmake_minimum_required(VERSION 3.10)
project(testsPRNGTreeC)

# create the test executable
add_executable(testsPRNGTreeC testsPRNGTree.c)

# link the PRNGTree library 
target_link_libraries(testsPRNGTreeC PRIVATE PRNGTreeLib m)

# enable AddressSanitizer for debugging
target_compile_options(testsPRNGTreeC PRIVATE -fsanitize=address -g)
target_link_options(testsPRNGTreeC PRIVATE -fsanitize=address)