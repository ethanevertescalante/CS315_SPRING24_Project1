//
// Created by Ethan on 2/12/2024.
//

#include "TraversableStack.hpp"
#include <iostream>
void TraversableStack::addLast(Token token) {
    tagNames.push_back(token);

}

Token TraversableStack::popLast() {
    if(!tagNames.empty()) {
        Token lastTokenInStack = tagNames.back();
        tagNames.pop_back();
        tagNames.shrink_to_fit();
        return lastTokenInStack;
    }
}

Token TraversableStack::last() {
    if(!tagNames.empty()){
        Token lastTokenInStack = tagNames.back();
        return lastTokenInStack;
    }
}

bool TraversableStack::rmember(std::string tag) {
    for(std::vector<Token>::iterator iter = tagNames.begin(); iter != tagNames.end(); iter++)
    {
        if(iter->tagName() == tag)
        {
            return true;
        }
    }

    return false;

}

void TraversableStack::rremove(std::string tag) {
    for(std::vector<Token>::iterator iter = tagNames.begin(); iter != tagNames.end(); iter++)
    {
        if(iter->tagName() == tag)
        {
            tagNames.erase(iter);
        }
    }
}

void TraversableStack::printBackwardUnit(std::string tag, bool indent) {
    for(std::vector<Token>::iterator iter = tagNames.begin(); iter != tagNames.end(); iter++){
        if(iter->tagName() == tag)
        {
            if(indent)
            {
                std::cout << "\t";
            }
            iter->print();
            std::cout << std::endl;
        }
    }
}


size_t TraversableStack::size() {
    return tagNames.size();
}

bool TraversableStack::empty() {
    return tagNames.empty();
}