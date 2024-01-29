//
// Created on 1/21/24.
//

#include <iostream>
#include <iomanip>
#include "Token.hpp"

Token::Token(int line, int pos): _isOpenTag{false},
                                 _isCloseTag{false},
                                 _isCloseAngleBracket{false},
                                 _isCloseStandAloneTag{false},
                                 _tagName{""},
                                 _eof{false},
                                 _lineNumber{line},
                                 _charPos{pos} {}

bool &Token::isOpenTag() { return _isOpenTag; }
bool &Token::isCloseTag() { return _isCloseTag; }

bool &Token::isCloseAngleBracket() { return _isCloseAngleBracket; }

bool &Token::endOfFile() { return _eof; }
bool &Token::isCloseStandAloneTag() { return _isCloseStandAloneTag; }

std::string Token::tagName() { return _tagName; }

void Token::makeOpenTag(std::string name) {
    _tagName = name;
    isOpenTag() = true;
}

void Token::makeCloseTag(std::string name) {
    _tagName = name;
    isCloseTag() = true;
}

void Token::print() {
    std::cout << "[" << std::setw(2) << _lineNumber << ", " <<  std::setw(3) << _charPos << "] ";

    if(isOpenTag()) {
        std::cout << "<" << tagName() << std::endl;
    } else if(isCloseStandAloneTag()) {
        std::cout << "[" << _lineNumber << ", " << _charPos << "] ";
        std::cout << "/>";
    } else {  // more else if's before this else
        std::cout << "Unknown token\n";
    }
}
