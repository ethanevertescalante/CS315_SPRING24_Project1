//
// Created by Ethan on 2/12/2024.
//

#ifndef CS315_PROJECT1_PHASE1_TAGPARSER_HPP
#define CS315_PROJECT1_PHASE1_TAGPARSER_HPP

#include "TraversableStack.hpp"
#include "Tokenizer.hpp"

class TagParser {

public:
    TagParser();
    void parseTags(std::string nameOfInputFile);

private:
    TraversableStack stack;
    std::pair<Token, Token> openClosePair;
    Token OpenToken = openClosePair.first;
    Token CloseToken = openClosePair.second;



    std::vector< std::pair<Token,Token> > tagLocations;


    std::map<std::string, std::vector< std::pair<Token, Token> > > allTagLocations;

    void handleOpenTag(Tokenizer &tokenizer, Token &token);
    void handleCloseTag(Tokenizer &tokenizer, Token &token);

    void handleStandAloneCloseTag(Token &token);
    void printWellFormedTags();

};


#endif //CS315_PROJECT1_PHASE1_TAGPARSER_HPP
