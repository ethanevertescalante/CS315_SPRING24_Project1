//
// Created on 1/21/24.
//

#include <iostream>

#include "Tokenizer.hpp"

Tokenizer::Tokenizer(std::string name): lineNumber{1},
                                        charPosition{1},
                                        inputFileName{name} {
    inputStream.open(inputFileName, std::ios::in);  // open the input file. We will make sure that it is open in getToken.
}

bool Tokenizer::charOfInterest(char c) {
    // is c the initial (or the sole) character of a token?
    if(std::isspace(c) || std::isalpha(c) || c == '<' || c == '>') //special characters that we have to keep track of
    {
        return true; // if c is charOfInterest, then return true
    }

    return false; //or else no char of interest

}

Token Tokenizer::getToken() {
    char c;

    if( ! inputStream.is_open()) {
        std::cout << "Tokenizer::getToken() called with a stream that is not open." << std::endl;
        std::cout << "Make sure that " << inputFileName << " exists and is readable. Terminating.";
        exit(2);
    }

    while( inputStream.get(c) && ! charOfInterest(c) ) {
        // keep track of the line number and the character position here.
        if(c == '\n') //check for new line
        {
            lineNumber++; //adding one to line number
            charPosition = 1; //reset the character position
        }else
        {
            charPosition++; //or else keep track of the line position
        }

    }

    Token token(lineNumber, charPosition);
    if( inputStream.eof() ) {
        token.endOfFile() = true;
    } else if( c == '<' ) {
        // Immediately after an open angle-bracket, we will have to see
        // the tag name. That is, at this point, inputStream.peek() should
        // be a letter. If it is, then read the tag name, create an
        // open tag token for it. If inputStream.peek() is not a letter,
        // you will return a token that represents "random" open angle-bracket.

        token.isOpenTag() = true; //open tag is true;

        //declaration
        char peekingChar = inputStream.peek();
        char carryingChar;
        std::string tName;

        if(std::isalpha(peekingChar)) //checking if the peekingChar is an alphabetical character
        {

            inputStream.get(carryingChar); //getting the first letter
            tName += carryingChar; //moving the first letter into tName (name of tag)
            while(carryingChar != ' ') //while a space is not the carrying character
            {
                tName += carryingChar; //add the next character to tName (name of tag)

            }
        }


        token.makeOpenTag(tName);




        /*
               Let's assume that there was a tag name after the < and that it contained
               em. Here is how we create a token for it.

               std::string tName = "em"; // suppose we have read and stored em in tName -- this is a hard-coded example for demo
               token.makeOpenTag(tName);
            */
    } else if( c == '>' ) {
        token.isCloseAngleBracket() = true;
        return token;
    }// ... more if-else statements here, followed by a final else.


    return token;

}
