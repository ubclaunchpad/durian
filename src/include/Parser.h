#pragma once

#include <Lexer.h>
#include <ASTree.h>
#include <exception>

class Parser {
    Lexer m_lexer;
    Token m_currToken;
public:
    explicit Parser(const Lexer& lexer);
    std::unique_ptr<AST::Stmt> parse();
private:
    void eatToken(TokenType tok);
    std::unique_ptr<AST::Stmt> parseStmt();
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
