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
    std::map<std::string, std::vector< std::pair<Token, Token> > > allTagLocations;

    Token openTag;
    Token closeTag;

    std::vector< std::pair<Token, Token> > tagLocations;



    void handleOpenTag(Tokenizer &tokenizer, Token &token);
    void handleCloseTag(Tokenizer &tokenizer, Token &token);
    void handleStandAloneCloseTag(Token &token);
    void printWellFormedTags();
    void pairTokens(std::string tagName);
    void mapPair(std::string tagName, std::pair<Token, Token>  pairTags);

};


#endif //CS315_PROJECT1_PHASE1_TAGPARSER_HPP
