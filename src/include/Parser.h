#pragma once

#include <Lexer.h>
#include <ASTree.h>
#include <util.h>
#include <exception>

class Parser {
    Lexer m_lexer;
public:
    explicit Parser(Lexer lexer);
    std::unique_ptr<AST::Stmt> parse();
private:
    // Parsers
    std::unique_ptr<AST::Stmt> parseStmt();
    std::unique_ptr<AST::IfStmt> parseIfStmt();
    std::unique_ptr<AST::BlockStmt> parseBlockStmt();
    std::unique_ptr<AST::Expr> parseExpr();
};

/*
class YourDurianHasGoneBadException : public std::exception {
    int m_line;
    Token m_invalidToken;
    Statement m_statement;
public:
    YourDurianHasGoneBadException(const char* message, int line,
                                  Token invalidToken, Statement statement)
        : std::exception(message)
        , m_line(line)
        , m_invalidToken(invalidToken)
        , m_statement(statement)
    {

    }
};
 */
