
#include <iostream>
#include <fstream>
#include <cstring>
#include "Tokenizer.hpp"

int main(int argc, char *argv[]) {
/*
    if( argc != 2 ) {  // we expect the name of the file as an argument to the program.
        std::cout << "usage: " << argv[0] << " nameOfAnInputFile" << std::endl;
        exit(1);
    }
  */

    std::string  inputFile;

    std::cout << "Input File: ";
    std::cin >> inputFile;
    // Here, we open the file to make sure that it exists before starting the program.
    // When using CLion, the input file has to be in cmake-build-debug directory.

    std::ifstream inputStream;
    inputStream.open(inputFile, std::ios::in);    // open for reading
    if( ! inputStream.is_open()) {
        std::cout << "Unable to open " << argv[1] << ". Terminating...";
        std::cout << strerror(errno) << std::endl;
        exit(2);
    }

    // We now know that the input file exists, and we can read from it. Here, we will close it
    // and give Tokenizer the name of the file, so it can open and use it. We also could give
    // Tokenizer 'inputStream' so that it just uses it.
    inputStream.close();
/*
    Tokenizer tokenizer(inputFile);   // use the first argument, which contains the name of the input file
    // to create an instance of Tokenizer.
    Token token = tokenizer.getToken();  // get the first token.

    token.print();
*/

    // this is what the main function for your solution to phase 1 should look like.

    Tokenizer tokenizer(inputFile);
    Token token = tokenizer.getToken();  // get the first token to start the while loop

    while( ! token.endOfFile()) {
        token.print();
        token = tokenizer.getToken();
    }


    return 0;
}
