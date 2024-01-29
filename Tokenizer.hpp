//
// Created by Ali Kooshesh on 1/21/24.
//

#ifndef CS315_PROJECT1_PHASE1_TOKENIZER_HPP
#define CS315_PROJECT1_PHASE1_TOKENIZER_HPP


#include <string>
#include <fstream>
#include <map>
#include "Token.hpp"

class Tokenizer {

public:
    Tokenizer(std::string);
    Token getToken();

private:
    int lineNumber, charPosition;
    std::string inputFileName;
    std::ifstream inputStream;

    bool charOfInterest(char c);
};


#endif //CS315_PROJECT1_PHASE1_TOKENIZER_HPP
