#pragma once

#include <Lexer.h>

class Parser {
    Lexer m_lexer;
public:
    Parser(const std::string input);
};

