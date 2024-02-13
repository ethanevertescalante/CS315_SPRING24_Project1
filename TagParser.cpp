//
// Created by Ethan on 2/12/2024.
//

#include "TagParser.hpp"
#include "Token.hpp"
#include <iostream>



void TagParser::parseTags(std::string nameOfInputFile) {
    Tokenizer tokenizer(nameOfInputFile);


    Token token = tokenizer.getToken();
    while (!token.endOfFile()) {
        if( token.isOpenTag() )
            handleOpenTag(tokenizer, token);
        else if( token.isCloseTag() )
            handleCloseTag(tokenizer, token);
        else if(token.isCloseAngleBracket() || token.isOpenAngleBracket()) {
            token.print();
            std::cout << (token.isCloseAngleBracket() ? " ignoring random close angle-bracket."
                                                    : " ignoring random open angle-bracket.") << std::endl;
        } else {
            token.print();
            std::cout << " unknown token."  << std::endl;
        }
        token = tokenizer.getToken();
    }
// tokens have finished, but you want to determine if
// there are any open tags that have not been matched.

    while(!stack.empty()){
       Token noMatchingCloseTag = stack.last();
       noMatchingCloseTag.print();
       std:: cout << "doesn't have a matching close tag. Will discard it." << std::endl;
       stack.rremove(noMatchingCloseTag.tagName());
   }

}

void TagParser::handleOpenTag(Tokenizer &tokenizer, Token &token) {


}

void TagParser::handleCloseTag(Tokenizer &tokenizer, Token &token) {

}

void TagParser::handleStandAloneCloseTag(Token &token) {

}

void TagParser::printWellFormedTags() {
    std::cout << "The following is a list of well-formed HTML tags." << std::endl;


}