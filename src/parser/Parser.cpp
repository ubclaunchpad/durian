#include <Parser.h>
#include <iostream>

Parser::Parser(const Lexer lexer)
    : m_lexer(lexer)
{
    m_currToken = m_lexer.getToken();
}

Token Parser::eatToken(TokenType tok) {
    if (m_currToken.type != tok) {
        std::cerr << "Unexpected token " << m_currToken.toString() << " at line " << m_currToken.line << std::endl;
        exit(1);
    }
    return m_currToken = m_lexer.getToken();
}

std::unique_ptr<AST::Stmt> Parser::parse() {
    return parseStmt();
}

std::unique_ptr<AST::Stmt> Parser::parseStmt(){
    if (m_currToken.type == TokenType::If) {
        eatToken(TokenType::If);
        std::unique_ptr<AST::Expr> cond = parseExpr();
        std::unique_ptr<AST::BlockStmt> body = parseBlockStmt();

        return std::unique_ptr<AST::IfStmt>(new AST::IfStmt(std::move(cond), std::move(body), nullptr));
        // TODO handle else case
    }

    if (m_currToken.type == TokenType::While) {
        eatToken(TokenType::While);
        std::unique_ptr<AST::Expr> cond = parseExpr();
        std::unique_ptr<AST::BlockStmt> body = parseBlockStmt();

        return std::unique_ptr<AST::WhileStmt>(new AST::WhileStmt(std::move(cond), std::move(body)));
    }

    if (m_currToken.type == TokenType::Next) {
        eatToken(TokenType::Next);
        return std::unique_ptr<AST::NextStmt>(new AST::NextStmt());
    }

    if (m_currToken.type == TokenType::Break) {
        eatToken(TokenType::Break);
        return std::unique_ptr<AST::BreakStmt>(new AST::BreakStmt());
    }

    if (m_currToken.type == TokenType::Let) {
        eatToken(TokenType::Let);
        Token id = eatToken(TokenType::Identifier);
        eatToken(TokenType::Equal);
        std::unique_ptr<AST::Expr> val = parseExpr();
        return std::unique_ptr<AST::LetStmt>(new AST::LetStmt(std::unique_ptr<AST::Identifier>(new AST::Identifier(id.literal)), std::move(val)));
    }

    if (m_currToken.type == TokenType::Print) {
        eatToken(TokenType::Print);
        std::unique_ptr<AST::Expr> expr = parseExpr();
        return std::unique_ptr<AST::PrintStmt>(new AST::PrintStmt(std::move(expr)));
    }

    if (m_currToken.type == TokenType::Err) {
        eatToken(TokenType::Err);
        std::unique_ptr<AST::Expr> expr = parseExpr();
        return std::unique_ptr<AST::ErrStmt>(new AST::ErrStmt(std::move(expr)));
    }

    if (m_currToken.type == TokenType::Scan) {
        eatToken(TokenType::Scan);
        Token id = eatToken(TokenType::Identifier);
        return std::unique_ptr<AST::ScanStmt>(new AST::ScanStmt(std::unique_ptr<AST::Identifier>(new AST::Identifier(id.literal))));
    }

    if (m_currToken.type == TokenType::Def) {
        // TODO
    }

    if (m_currToken.type == TokenType::Return) {
        eatToken(TokenType::Return);
        std::unique_ptr<AST::Expr> expr = parseExpr();
        return std::unique_ptr<AST::ReturnStmt>(new AST::ReturnStmt(std::move(expr)));
    }

    // assignment or expr statement
    std::unique_ptr<AST::Expr> expr = parseExpr();
    if (m_currToken.type == TokenType::Equal) {
        eatToken(TokenType::Equal);
        std::unique_ptr<AST::Expr> rval = parseExpr();
        // TODO: add checks that lval is valid.
        return std::unique_ptr<AST::AssignStmt>(new AST::AssignStmt(std::move(expr), std::move(rval)));
    } else {
        return std::unique_ptr<AST::ExprStmt>(new AST::ExprStmt(std::move(expr)));
    }

    // this is how I do error handling lol.
    exit(1);
}


std::unique_ptr<AST::BlockStmt> Parser::parseBlockStmt() {
    eatToken(TokenType::LeftBrace);
    std::vector<std::unique_ptr<AST::Stmt>> statements;
    while (m_currToken.type != TokenType::RightBrace) {
        statements.push_back(parseStmt());
        eatToken(TokenType::EOL);
    }
    eatToken(TokenType::RightBrace);
    return std::unique_ptr<AST::BlockStmt>(new AST::BlockStmt(std::move(statements)));
}

std::unique_ptr<AST::Expr> Parser::parseExpr() {
    // TODO
    return nullptr;
}
