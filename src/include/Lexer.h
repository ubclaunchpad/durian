#pragma once

#include <string>

#include <Token.h>

class Lexer {
    const std::string m_input;
    std::string::const_iterator m_iter;
    uint32_t m_line;
public:
    Lexer(const std::string input);

    Token getToken();
private:
    bool isDigit(const char c);
    bool isAlpha(const char c);
    bool isIdentChar(const char c);
};


