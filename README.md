# Software Engineering Project 2025–2026  
**University:** [Polytechnic of Milan](https://www.polimi.it/en)  
**Authors:** [Emanuele Brotti](mailto:emanuele.brotti@polimi.it), [Enrico Chen](mailto:enrico.chen@polimi.it)  
**Professor Supervisor:** [Alessandro Barenghi](https://barenghi.faculty.polimi.it/doku.php)  

## Project Overview
This repository contains a C library implementing a PRNG‑based binary tree data structure designed for experimentation, educational purposes and testing. The library provides utilities for building, manipulating and traversing pseudo‑randomly generated trees, enabling deterministic reproducibility through fixed seeds. It is intended to be lightweight, portable and easily integrable into other C projects.

The project was developed as part of the *Software Engineering project* (Academic Year 2025–2026) at the **Polytechnic of Milan**.  
The project was designed and built by **Emanuele Brotti** and **Enrico Chen**, under the academic supervision of **Prof. Alessandro Barenghi**.

## Course Information
- **Name:** PROGETTO DI INGEGNERIA INFORMATICA (5 CFU)  
- **Identification Code:** 089020
- **Degree:** BSc in Software Engineering  
- **Institution:** Polytechnic of Milan, DEIB  
- **Academic Year:** 2025–2026

## Technical Stack
- **Language:** C
- **Build Tools:** GCC, CMake
- **External Dependencies:** [CROSS Implementation](https://github.com/CROSS-signature/CROSS-implementation)

## Importing This Library Into Your CMake Project
To include this library in your own C project using CMake, follow these steps:
<ol>
    <li> Clone the repository folder inside your project directory (for example next to your main <code>CMakeLists.txt</code>). </li>
    <li> Include the library using <code>add_subdirectory()</code> in your main <code>CMakeLists.txt</code>. </li>
    <li> Link the library target <code>PRNGTreeLib</code> to your executable. </li>
    <li> <em>(Optional)</em> Enable debugging tools such as AddressSanitizer. </li>
</ol>

Below is an example `CMakeLists.txt` configuration:
```
cmake_minimum_required(VERSION 3.10)
project(UserProject)

# use C11
set(CMAKE_C_STANDARD 11)

# include the software-engineering-project subdirectory
add_subdirectory(software-engineering-project)

# create the executable
add_executable(UserProgram test.c)

# link the PRNGTreeLib library
target_link_libraries(UserProgram PRIVATE PRNGTreeLib)

# Enable AddressSanitizer for debugging
target_compile_options(UserProgram PRIVATE -fsanitize=address -g)
target_link_options(UserProgram PRIVATE -fsanitize=address)
```

After configuring CMake, from the project root, build with:
```
cmake -S . -B build
```
then, compile and run with:
```
cmake --build build
./build/UserProgram
```

## License
This project is released under the MIT License. You are free to use, modify, and distribute the software in accordance with the terms of the MIT License.
