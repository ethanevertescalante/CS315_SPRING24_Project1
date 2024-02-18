//
// Created by Ethan on 2/12/2024.
//

#include "TagParser.hpp"
#include "Token.hpp"
#include <iomanip>
#include <iostream>

TagParser::TagParser(): openTag(0,0), closeTag(0,0) {}


void TagParser::parseTags(std::string nameOfInputFile) {
    Tokenizer tokenizer(nameOfInputFile);

    Token token = tokenizer.getToken(); // gets the first token to start
    while (!token.endOfFile()) {
        if( token.isOpenTag() )
            handleOpenTag(tokenizer, token);
        else if( token.isCloseTag() )
            handleCloseTag(tokenizer, token);
        else if(token.isCloseStandAloneTag())
            handleStandAloneCloseTag(token);
        else if(token.isCloseAngleBracket() || token.isOpenAngleBracket()) {
            token.print();
            std::cout << (token.isCloseAngleBracket() ? " ignoring random close angle-bracket."
                                                      : " ignoring random open angle-bracket.") << std::endl;
        } else {
            token.print();
            std::cout << " unknown token."  << std::endl;
        }

        token = tokenizer.getToken(); //get next token

    }
// tokens have finished, but you want to determine if
// there are any open tags that have not been matched.

    while(!stack.empty()){
        Token noMatchingCloseTag = stack.last();
        noMatchingCloseTag.print();
        std::cout << " doesn't have a matching close tag. Will discard it." << std::endl;

        stack.popLast();
    }

    printWellFormedTags();

}

void TagParser::handleOpenTag(Tokenizer &tokenizer, Token &token) {
    std::string tName = token.tagName();
    Token nextToken = tokenizer.getToken(); //stores next token

    stack.addLast(token);
    if(nextToken.isCloseStandAloneTag())
    {
        handleStandAloneCloseTag(nextToken);
    }else if(!nextToken.isCloseAngleBracket()){
        token.print();
        stack.popLast();
        std::cout << " is missing a '>' or  '/>. Will discard it.\n";

        token = tokenizer.getToken(); //skipping the next token
    }

    /*
     //new vars
     Token nextToken = tokenizer.getToken(); //stores next token
     std::string tName = token.tagName(); //stores token name

     stack.addLast(token); //add initial token to stack

     if(nextToken.isCloseStandAloneTag())
     {
         handleStandAloneCloseTag(nextToken);
     }else if(!nextToken.isCloseAngleBracket()) {
         token.print();
         stack.popLast();
         std::cout << " is missing a '>' or  '/>. Will discard it.\n";
        // stack.popLast(); //take the mal token out of stack
         token = tokenizer.getToken(); //skipping the next token
    }

 */
}

void TagParser::handleCloseTag(Tokenizer &tokenizer, Token &token) {

    Token nextToken = tokenizer.getToken(); //stores next token
    std::string nameTag = token.tagName();

    if(!stack.rmember(nameTag))
    {
        token.print();
        std::cout << " doesn't have a matching open tag. Will discard it.\n";
    }else {
        stack.addLast(token);
        if (!nextToken.isCloseAngleBracket()) {
            token.print();
            stack.popLast();
            std::cout << " is missing a '>' or  '/>. Will discard it.\n";
            token = tokenizer.getToken();
        }
        pairTokens(nameTag);
    }


}

void TagParser::handleStandAloneCloseTag(Token &token) {
    std::string tagName = token.tagName();
    std::pair<Token, Token> pairOfTags = {openTag, closeTag};

    openTag = stack.last();
    closeTag = token;
    stack.popLast();

    pairOfTags.first = openTag;
    pairOfTags.second = closeTag;

    tagLocations.push_back(pairOfTags);
    mapPair(openTag.tagName(), pairOfTags);


}

void TagParser::pairTokens(std::string tagName) {
    /*
    Token openTag(0,0);
    Token closeTag(0,0);
    std::pair<Token, Token> pairOfTags = {openTag, closeTag};
    std::vector< std::pair<Token, Token> > tagLocations;

    openTag = stack.last();
    closeTag = token;
    stack.popLast();


    pairOfTags.first = openTag;
    pairOfTags.second = closeTag;



    tagLocations.push_back(pairOfTags);
    mapPair(tagName, pairOfTags);

*/

    std::pair<Token, Token> pairOfTags = {openTag, closeTag};
    while(stack.rmember(tagName))
    {

        if(stack.last().isOpenTag())
        {
            openTag = stack.last();
            pairOfTags.first = openTag;
            stack.popLast();

        }else if(stack.last().isCloseTag())
        {
            closeTag = stack.last();
            pairOfTags.second = closeTag;
            stack.popLast();

        }



    }

    tagLocations.push_back(pairOfTags);
    mapPair(tagName, pairOfTags);

}

void TagParser::mapPair(std::string tagName, std::pair<Token, Token> pairTags) {

    allTagLocations[tagName] = std::vector<std::pair< Token, Token>>();
    allTagLocations[tagName].push_back(pairTags);

}



void TagParser::printWellFormedTags() {
    std::cout << "The following is a list of well-formed HTML tags." << std::endl;
    std::cout << std::endl;
    for (auto mapIter = allTagLocations.begin(); mapIter != allTagLocations.end(); ++mapIter) {
        // our map, pairs an array of Tokens with tag-name strings.
        std::cout << mapIter->first << " appeared in the following " << mapIter->first.size() << " location(s)." << std::endl;
        std::vector<std::pair<Token, Token>> locations = mapIter->second;
        for(auto vIter = locations.begin(); vIter != locations.end(); vIter++) {
            // Each element in the vector is a pair of tokens.
            std::cout << "\t";
            vIter->first.print();
            std::cout << std::setw(3) << "--" << std::setw(2);
            vIter->second.print();
            std::cout << std::endl;
        }

        std::cout << std::endl;

    }
}