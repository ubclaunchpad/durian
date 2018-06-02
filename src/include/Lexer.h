#pragma once

#include <string>

#include <Token.h>

class Lexer {
private:
    const std::string m_input;
    std::string::const_iterator m_iter;
    uint32_t m_line;
public:
    Lexer(const std::string input);
    Token getToken();
};


