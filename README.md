# Computer Engineering Project 2024–2025  
**University:** [Polytechnic of Milan](https://www.polimi.it/en)  
**Authors:** [Emanuele Brotti](mailto:emanuele.brotti@polimi.it), [Enrico Chen](mailto:enrico.chen@polimi.it)  
**Professor Supervisor:** [Alessandro Barenghi](https://barenghi.faculty.polimi.it/doku.php)  

## Project Overview
This repository contains a C library implementing a PRNG‑based binary tree data structure designed for experimentation, educational purposes and testing. The library provides utilities for building, manipulating and traversing pseudo‑randomly generated trees, enabling deterministic reproducibility through fixed seeds. It is intended to be lightweight, portable and easily integrable into other C projects.

The project was developed as part of the *Computer Engineering Project* (Academic Year 2024–2025) at the **Polytechnic of Milan**.  
The project was designed and built by **Emanuele Brotti** and **Enrico Chen**, under the academic supervision of **Prof. Alessandro Barenghi**.

**Documentation**: [PRNGTreeLibraryDoc.pdf](docs/PRNGTreeLibraryDoc.pdf)

## Course Information
- **Name:** PROGETTO DI INGEGNERIA INFORMATICA (5 CFU)  
- **Identification Code:** 089020
- **Degree:** BSc in Computer Engineering  
- **Institution:** Polytechnic of Milan, DEIB  
- **Academic Year:** 2024–2025

## Technical Stack
- **Language:** C
- **Build Tools:** CLang, CMake
- **External Dependencies:** [CROSS Implementation](https://github.com/CROSS-signature/CROSS-implementation)

## Importing This Library in your own C project using CMake
From the directory containing your main <code>CMakeLists.txt</code>, run: <br>
<code> git clone https://github.com/enricochen42/prng-tree-lib.git </code> <br>

Inside your main <code> CMakeLists.txt</code>:
<ol>
    <li> Include the library, using <code>add_subdirectory()</code>.
    <li> Link the library target <code>PRNGTreeLib</code> to your executable, using <code>target_link_libraries()</code>. </li>
    <li> <em>(Optional)</em> Enable debugging tools such as AddressSanitizer. </li>
</ol>

Below is a template for your `CMakeLists.txt` configuration:
```
cmake_minimum_required(VERSION 3.10)
project(nameProject)

# use C11
set(CMAKE_C_STANDARD 11)

# include the library subdirectory
add_subdirectory(prng-tree-lib)

# create the executable
add_executable(nameProgram nameFile.c)

# link the PRNGTreeLib library
target_link_libraries(nameProgram PRIVATE PRNGTreeLib)

# (optional) enable AddressSanitizer for debugging
target_compile_options(nameProgram PRIVATE -fsanitize=address -g)
target_link_options(nameProgram PRIVATE -fsanitize=address)
```

After configuring CMake, build the project from your main <code>CMakeLists.txt</code> directory, using:
```
cmake -S . -B build
```
Then, compile and run with:
```
cmake --build build
./build/nameProgram
```

## License
This project is released under the MIT License. You are free to use, modify, and distribute the software in accordance with the terms of the MIT License.
