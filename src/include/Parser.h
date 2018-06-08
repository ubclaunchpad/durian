#pragma once

#include <Lexer.h>
#include <ASTree.h>

class Parser {
    Lexer m_lexer;

public:
    Parser(const std::string input);
    std::unique_ptr<ASTree> buildTree();

};
