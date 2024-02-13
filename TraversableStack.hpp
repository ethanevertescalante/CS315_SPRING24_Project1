//
// Created by Ethan on 2/12/2024.
//

#include "Token.hpp"
#include <vector>
#ifndef CS315_PROJECT1_PHASE1_TRAVERSABLESTACK_HPP
#define CS315_PROJECT1_PHASE1_TRAVERSABLESTACK_HPP


class TraversableStack {

public:
    void addLast(Token token); // add to the top of the stack
    Token popLast();     // pop the top element of the stack
    Token last();        // top element of the stack
    bool rmember(std::string tag);  // perform a search from top to bottom
    void rremove(std::string tag);  // remove the last occurrence of a tag.
    void printBackwardUnit(std::string tag, bool indent=false);
    size_t size();  // how many element are on the stack?
    bool empty();

private:
    std::vector<Token> tagNames;
};



#endif //CS315_PROJECT1_PHASE1_TRAVERSABLESTACK_HPP
