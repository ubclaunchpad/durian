#include <Parser.h>

Parser::Parser(const Lexer lexer)
    : m_lexer(lexer)
{
    m_currenttoken = m_lexer.getToken();
}

Token Parser::eattoken(TokenType t) {
    if (m_currenttoken.type != t) {
        puts("Unexpected token type.");
        exit(1);
    }
    m_currenttoken = m_lexer.getToken();
}

std::unique_ptr<AST::Stmt> Parser::parse() {
    return parseStmt();
}

std::unique_ptr<AST::Stmt> Parser::parseStmt(){
    if (m_currenttoken.type == TokenType::If) {
        eattoken(TokenType::If);
        std::unique_ptr<AST::Expr> cond = parseExpr();
        std::unique_ptr<AST::BlockStmt> body = parseBlockStmt();

        return std::unique_ptr<AST::IfStmt>(new AST::IfStmt(std::move(cond), std::move(body), nullptr));
        // TODO handle else case
    }

    if (m_currenttoken.type == TokenType::While) {
        eattoken(TokenType::While);
        std::unique_ptr<AST::Expr> cond = parseExpr();
        std::unique_ptr<AST::BlockStmt> body = parseBlockStmt();

        return std::unique_ptr<AST::WhileStmt>(new AST::WhileStmt(std::move(cond), std::move(body)));
    }

    if (m_currenttoken.type == TokenType::Next) {
        eattoken(TokenType::Next);
        return std::unique_ptr<AST::NextStmt>(new AST::NextStmt());
    }

    if (m_currenttoken.type == TokenType::Break) {
        eattoken(TokenType::Break);
        return std::unique_ptr<AST::BreakStmt>(new AST::BreakStmt());
    }

    if (m_currenttoken.type == TokenType::Let) {
        eattoken(TokenType::Let);
        Token id = eattoken(TokenType::Identifier);
        eattoken(TokenType::Equal);
        std::unique_ptr<AST::Expr> val = parseExpr();
        return std::unique_ptr<AST::LetStmt>(new AST::LetStmt(std::unique_ptr<AST::Identifier>(new AST::Identifier(id.literal)), std::move(val)));
    }

    if (m_currenttoken.type == TokenType::Print) {
        eattoken(TokenType::Print);
        std::unique_ptr<AST::Expr> expr = parseExpr();
        return std::unique_ptr<AST::PrintStmt>(new AST::PrintStmt(std::move(expr)));
    }

    if (m_currenttoken.type == TokenType::Err) {
        eattoken(TokenType::Err);
        std::unique_ptr<AST::Expr> expr = parseExpr();
        return std::unique_ptr<AST::ErrStmt>(new AST::ErrStmt(std::move(expr)));
    }

    if (m_currenttoken.type == TokenType::Scan) {
        eattoken(TokenType::Scan);
        Token id = eattoken(TokenType::Identifier);
        return std::unique_ptr<AST::ScanStmt>(new AST::ScanStmt(std::unique_ptr<AST::Identifier>(new AST::Identifier(id.literal))));
    }

    if (m_currenttoken.type == TokenType::Def) {
        // TODO
    }

    if (m_currenttoken.type == TokenType::Return) {
        eattoken(TokenType::Return);
        std::unique_ptr<AST::Expr> expr = parseExpr();
        return std::unique_ptr<AST::ReturnStmt>(new AST::ReturnStmt(std::move(expr)));
    }

    // assignment or expr statement
    std::unique_ptr<AST::Expr> expr = parseExpr();
    if (m_currenttoken.type == TokenType::Equal) {
        eattoken(TokenType::Equal);
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
    eattoken(TokenType::LeftBrace);
    std::vector<std::unique_ptr<AST::Stmt>> statements;
    while (m_currenttoken.type != TokenType::RightBrace) {
        statements.push_back(parseStmt());
        eattoken(TokenType::EOL);
    }
    eattoken(TokenType::RightBrace);
    return std::unique_ptr<AST::BlockStmt>(new AST::BlockStmt(std::move(statements)));
}

std::unique_ptr<AST::Expr> Parser::parseExpr() {
    // TODO
    return nullptr;
}
