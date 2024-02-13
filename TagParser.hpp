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

    void handleOpenTag(Tokenizer &, Token &);
    void handleCloseTag(Tokenizer &, Token &);
    void handleStandAloneCloseTag(Token &);
    void printWellFormedTags();

};


#endif //CS315_PROJECT1_PHASE1_TAGPARSER_HPP
