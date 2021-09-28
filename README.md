# id ("identifier")

Provides id ("identifier") interface implementation,
according to the following rules:

Identifier is a literal string, split into groups.

Each of the groups consist of two symbols, alphabetical and number. e.g. "A1"

Id must have from 1 to 10 groups, separated by '-'
 
Allowed letters are - A B C E H I K L N O P R S T U W X Y Z
Allowed numbers are - 1...9

## Project structure

* src - the main source directory, contains id class definition and implementation.
* test - unit test source directory for id class implementation.

## Build

To clone and build the project, run the following:

### Using default compiler
> **_NOTE:_** Requires CMake 3.14 or newer

    git clone https://github.com/ipchelnikov/id.git
    cd id
    cmake ./
    make all

### Using clang compiler
> **_NOTE:_** Requires CMake 3.14 or newer

    git clone https://github.com/ipchelnikov/id.git
    cd id
    cmake -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ ./
    make all
    
### Using Visual Studio
> **_NOTE:_** Requires **C++ CMake tools for Windows**

    git clone https://github.com/ipchelnikov/id.git
    Open id folder in Visual Studio 2019
    Switch to CMake target view
    Build->Build All

## Run

### On Linux

    # From the project root directory
    
    ./bin/id_test # Start unit tests
    make check # To verify all tests
    
### On Windoes

    "Build All" in Visual Studio CMake project
