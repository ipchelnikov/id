# id ("identifier")

Provides id ("identifier") interface implementation,
according to the following rules:

Identifier is a literal string, split into groups.

Each of the groups consist of two symbols, alphabetical and number. e.g. "A1"

Id must have from 1 to 10 groups, separated by '-'
 
Allowed letters are - A B C E H I K L N O P R S T U W X Y Z
Allowed numbers are - 1...9

## Build

To clone and build the project, run the following:
> **_NOTE:_** Requires CMake 3.14 or newer

### Using default compiler

    git clone https://github.com/ipchelnikov/id.git
    cd id
    cmake ./
    make all

### Using clang compiler

    git clone https://github.com/ipchelnikov/id.git
    cd id
    cmake -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ ./
    make all

## Run

    # From the project root directory
    
    ./bin/id_test # Start unit tests
    make check # To verify all tests
