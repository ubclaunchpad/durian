#pragma once

#include <Lexer.h>
#include <ASTree.h>
#include <util.h>
#include <exception>

class Parser {
    Lexer m_lexer;
    Token m_currToken;
public:
    explicit Parser(Lexer lexer);
    std::unique_ptr<AST::Stmt> parse();
private:
    // Parsers
    Token eatToken(TokenType tok);
    std::unique_ptr<AST::Stmt> parseStmt();
    std::unique_ptr<AST::IfStmt> parseIfStmt();
    std::unique_ptr<AST::BlockStmt> parseBlockStmt();
    std::unique_ptr<AST::Expr> parseExpr();
    std::unique_ptr<AST::Expr> parseOrExpr();
    std::unique_ptr<AST::Expr> parseAndExpr();
    std::unique_ptr<AST::Expr> parseEqExpr();
    std::unique_ptr<AST::Expr> parseCompExpr();
    std::unique_ptr<AST::Expr> parseConcatExpr();
    std::unique_ptr<AST::Expr> parseAddExpr();
    std::unique_ptr<AST::Expr> parseMulExpr();
    std::unique_ptr<AST::Expr> parseUnaryExpr();
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
