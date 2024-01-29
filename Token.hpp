//
// Created by Ali Kooshesh on 1/21/24.
//

#ifndef CS315_PROJECT1_PHASE1_TOKEN_HPP
#define CS315_PROJECT1_PHASE1_TOKEN_HPP

#include <string>

class Token {
public:
    Token(int, int);
    bool &isOpenTag();
    bool &isCloseTag();

    bool &isCloseAngleBracket();

    bool &endOfFile();
    bool &isCloseStandAloneTag();

    std::string tagName();

    void makeOpenTag(std::string);
    void makeCloseTag(std::string);
    void print();

private:
    bool _isOpenTag = false, _isCloseTag = false, _isCloseAngleBracket = false,
            _eof = false, _isCloseStandAloneTag = false;

    std::string _tagName;
    int _lineNumber, _charPos;
};

#endif //CS315_PROJECT1_PHASE1_TOKEN_HPP
