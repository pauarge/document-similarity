# document-similarity

This project implements Jaccard Similarity, Mihash Similarity and Locally Sensitive Hashing to detect and grade similarity between documents. 

This README is purely a howto guide to compile and execute the program. For more detailed information on the actual implementation, please refer to the docs/ folder. 

## Requirements

This project has been developed in C++, thus, a C++ compiler is required.

The Boost C++ library has also been used, therefore Boost must be installed on the system.

Finally, CMake is the system used to manage the building process, therefore it's also needed.

All these requirements are available and easy to install on all major desktop platforms.

## Comipiling

To compile, browse to the root directory of the project and execute `cmake CMakeLists.txt`. This will create the actual makefile and required files adapted to the current environment.

Then, run `make` and executables will be generated inside `bin/` folder.

## Running

To execute both the main script and the tests, a directory with `.txt` input files must be provided. The path can be relative or absolute.

To execute main program:

`bin/comparator test/set1`

To execute experiments:

`bin/experiments test/set1` 
