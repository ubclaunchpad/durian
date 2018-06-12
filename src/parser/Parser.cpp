#include <Parser.h>

Parser::Parser(const Lexer lexer)
    : m_lexer(lexer)
{

}

std::unique_ptr<AST::Stmt> Parser::parse() {
    return parseStmt();
}

std::unique_ptr<AST::Stmt> Parser::parseStmt(){
    Token currTok = m_lexer.getToken();
    if (currTok.type == TokenType::EOL || currTok.type == TokenType::END) {
        // TODO what to do here
        return nullptr;
    }
    if (currTok.type == TokenType::If) {
        // TODO
    }
    if (currTok.type == TokenType::While) {
        std::unique_ptr<AST::Expr> expr = parseExpr();
        currTok = m_lexer.getToken();
        if (currTok.type != TokenType::LeftBrace) {
            // TODO syntax error, synchronize
        }
        std::unique_ptr<AST::BlockStmt> body = parseBlockStmt();
        return std::unique_ptr<AST::WhileStmt>(new AST::WhileStmt(std::move(expr), std::move(body)));
    }
    if (currTok.type == TokenType::Next) {
        currTok = m_lexer.getToken();
        if (currTok.type != TokenType::EOL) {
            // TODO syntax error, synchronize
        }
        return std::unique_ptr<AST::NextStmt>(new AST::NextStmt());
    }
    if (currTok.type == TokenType::Break) {
        currTok = m_lexer.getToken();
        if (currTok.type != TokenType::EOL) {
            // TODO syntax error, synchronize
        }
        return std::unique_ptr<AST::BreakStmt>(new AST::BreakStmt());
    }
    if (currTok.type == TokenType::Let) {
        // TODO
    }
    if (currTok.type == TokenType::Print) {
        std::unique_ptr<AST::Expr> expr = parseExpr();
        currTok = m_lexer.getToken();
        if (currTok.type != TokenType::EOL) {
            // TODO syntax error, synchronize
        }
        return std::unique_ptr<AST::PrintStmt>(new AST::PrintStmt(std::move(expr)));
    }
    if (currTok.type == TokenType::Err) {
        std::unique_ptr<AST::Expr> expr = parseExpr();
        currTok = m_lexer.getToken();
        if (currTok.type != TokenType::EOL) {
            // TODO syntax error, synchronize
        }
        return std::unique_ptr<AST::ErrStmt>(new AST::ErrStmt(std::move(expr)));
    }
    if (currTok.type == TokenType::Scan) {
        // TODO
        Token ident = m_lexer.getToken();
        if (ident.type != TokenType::Identifier) {
            // TODO syntax error, synchronize
        }
        currTok = m_lexer.getToken();
        if (currTok.type != TokenType::EOL) {
            // TODO syntax error, synchronize
        }
    }
    if (currTok.type == TokenType::Def) {
        // TODO
    }
    if (currTok.type == TokenType::Return) {
        std::unique_ptr<AST::Expr> expr = parseExpr();
        currTok = m_lexer.getToken();
        if (currTok.type != TokenType::EOL) {
            // TODO syntax error, synchronize
        }
        return std::unique_ptr<AST::ReturnStmt>(new AST::ReturnStmt(std::move(expr)));
    }
    // assignment or expr statement
    std::unique_ptr<AST::Expr> expr = parseExpr();
    currTok = m_lexer.getToken();
    if (currTok.type == TokenType::EOL) {
        return expr;
    }
    if (currTok.type == TokenType::Equal) {
        std::unique_ptr<AST::Expr> rhs = parseExpr();
        return std::unique_ptr<AST::AssignStmt>(new AST::AssignStmt(std::move(expr), std::move(rhs)));
    }
    // TODO error handling
    return nullptr;
}


std::unique_ptr<AST::BlockStmt> Parser::parseBlockStmt() {
    // TODO
    return nullptr;
}

std::unique_ptr<AST::Expr> Parser::parseExpr() {
    // TODO
    return nullptr;
}
