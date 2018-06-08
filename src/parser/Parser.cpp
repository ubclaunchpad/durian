#include <Parser.h>

Parser::Parser(const std::string input)
    : m_lexer(input)
{

}

std::unique_ptr<ASTree> Parser::buildTree() {
    return nullptr;
}
