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
    // is c the initial (or the sole) character of a token
    if(c == '<' || c == '>' || c == '/'){ // if c is charOfInterest, then return true

        if (c =='/'){ //for standalone tag
            inputStream.get(c); //get next character
            charPosition++; //add to position
            if(c != '>') //if the next char is not a close bracket
            {
                return false;
            }
            inputStream.putback(c); //else putback character
            charPosition--; //sub position
        }

        return true;
    }
    return false;
}

Token Tokenizer::getToken() {
    char c;

    if( ! inputStream.is_open() ) {
        std::cout << "Tokenizer::getToken() called with a stream that is not open." << std::endl;
        std::cout << "Make sure that " << inputFileName << " exists and is readable. Terminating.";
        exit(2);
    }

    while( inputStream.get(c) && !charOfInterest(c) ) {
        // keep track of the line number and the character position here.
        if(c == '\n'){ //tracking line number
            lineNumber++;
        }
        charPosition++; //and character pos of non charOfInterest
    }

    //declarations that will be used in the following if statement
    char peekingChar = inputStream.peek();
    char carryingChar;
    std::string tName;

    Token token(lineNumber, charPosition);
    if( inputStream.eof() ) {
        token.endOfFile() = true;
    } else if( c == '<' ) { //open brackets
        charPosition++; //add char pos


        // Immediately after an open angle-bracket, we will have to see
        // the tag name. That is, at this point, inputStream.peek() should
        // be a letter. If it is, then read the tag name, create an
        // open tag token for it. If inputStream.peek() is not a letter,
        // you will return a token that represents "random" open angle-bracket.


        if(std::isalpha(peekingChar)){
            inputStream.get(carryingChar); //getting the character

            charPosition++;

            while(carryingChar != '>' && carryingChar != ' ') //making sure that the carrying character is not a space or '>'
            {

                tName += carryingChar; //add the next character to tName (name of tag)
                inputStream.get(carryingChar); //get next character
                charPosition++; //add to position


                if(carryingChar == '>')
                {
                    inputStream.putback(carryingChar); //putback the '>' for it to not get missed
                    charPosition--; //sub char pos
                }

            }

            token.makeOpenTag(tName); //make the open tag

        }else if(peekingChar == '/'){

            inputStream.get(carryingChar); // get next character

            charPosition++; //add char pos


            while(carryingChar != ' ' && carryingChar != '>') { //making sure that the carrying character is not a space or '>'

                tName += carryingChar; //add the next character to tName (name of tag)
                inputStream.get(carryingChar); //get next character
                charPosition++; //add to position

                if(carryingChar == '>'){
                    inputStream.putback(carryingChar);
                    charPosition--;
                }

            }
            token.makeCloseTag(tName);
        }



        /*
               Let's assume that there was a tag name after the < and that it contained
               em. Here is how we create a token for it.

               std::string tName = "em"; // suppose we have read and stored em in tName -- this is a hard-coded example for demo
               token.makeOpenTag(tName);
            */
    } else if( c == '/') {
        charPosition++; //add char pos
        if(peekingChar == '>') //check for standalone close tag
        {
            inputStream.get(carryingChar);
            charPosition++;
            token.isCloseStandAloneTag() = true;
        }


    }else{ //final case is if it is a '>'
        charPosition++;
        token.isCloseAngleBracket() = true;
        return token;
    }
    // ... more if-else statements here, followed by a final else.


    return token;

}
