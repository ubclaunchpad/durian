#pragma once

#include <string>

#include <Token.h>

class Lexer {
    const std::string m_input;
    std::string::const_iterator m_iter;
    uint32_t m_line;
public:
    explicit Lexer(const std::string& input);
    const Token getToken();
private:
    bool isDigit(char c) const;
    bool isAlpha(char c) const;
    bool isIdentChar(char c) const;
};


