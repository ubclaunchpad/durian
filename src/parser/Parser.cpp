#include <Parser.h>
#include <iostream>
#include <cstdlib>

Parser::Parser(const Lexer lexer)
        : m_lexer(lexer) {
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

std::unique_ptr<AST::Stmt> Parser::parseStmt() {
    if (m_currToken.type == TokenType::END) {
        return nullptr;
    }
    if (m_currToken.type == TokenType::EOL) {
        eatToken(TokenType::EOL);
        return parseStmt();
    }
    if (m_currToken.type == TokenType::If || m_currToken.type == TokenType::Elif) {
        eatToken(m_currToken.type);
        auto cond = parseExpr();
        auto body = parseBlockStmt();

        if (m_currToken.type == TokenType::Elif) {
            auto falseBody = parseStmt();
            return std::make_unique<AST::IfStmt>(std::move(cond),
                                                 std::move(body),
                                                 std::move(falseBody));
        } else if (m_currToken.type == TokenType::Else) {
            eatToken(TokenType::Else);
            auto falseBody = parseBlockStmt();
            return std::make_unique<AST::IfStmt>(std::move(cond),
                                                 std::move(body),
                                                 std::move(falseBody));
        }

        return std::make_unique<AST::IfStmt>(std::move(cond), std::move(body), nullptr);
    }

    if (m_currToken.type == TokenType::While) {
        eatToken(TokenType::While);
        auto cond = parseExpr();
        auto body = parseBlockStmt();

        return std::make_unique<AST::WhileStmt>(std::move(cond), std::move(body));
    }

    if (m_currToken.type == TokenType::Next) {
        eatToken(TokenType::Next);
        return std::make_unique<AST::NextStmt>();
    }

    if (m_currToken.type == TokenType::Break) {
        eatToken(TokenType::Break);
        return std::make_unique<AST::BreakStmt>();
    }

    if (m_currToken.type == TokenType::Let) {
        eatToken(TokenType::Let);
        Token id = eatToken(TokenType::Identifier);
        eatToken(TokenType::Equal);
        auto val = parseExpr();
        return std::make_unique<AST::LetStmt>(std::make_unique<AST::Identifier>(id.literal), std::move(val));
    }

    if (m_currToken.type == TokenType::Print) {
        eatToken(TokenType::Print);
        auto expr = parseExpr();
        return std::make_unique<AST::PrintStmt>(std::move(expr));
    }

    if (m_currToken.type == TokenType::Err) {
        eatToken(TokenType::Err);
        auto expr = parseExpr();
        return std::make_unique<AST::ErrStmt>(std::move(expr));
    }

    if (m_currToken.type == TokenType::Scan) {
        eatToken(TokenType::Scan);
        Token id = eatToken(TokenType::Identifier);
        return std::make_unique<AST::ScanStmt>(std::make_unique<AST::Identifier>(id.literal));
    }

    if (m_currToken.type == TokenType::Def) {
        eatToken(TokenType::Def);
        Token id = m_currToken;
        eatToken(TokenType::Identifier);
        eatToken(TokenType::LeftParen);
        std::vector<std::unique_ptr<AST::Identifier>> params;
        while (m_currToken.type != TokenType::RightParen) {
            Token param = m_currToken;
            eatToken(TokenType::Identifier);
            if (m_currToken.type != TokenType::RightParen) {
                eatToken(TokenType::Comma);
            }
            params.push_back(std::make_unique<AST::Identifier>(param.literal));
        }
        eatToken(TokenType::RightParen);
        auto body = parseBlockStmt();
        return std::make_unique<AST::FnDecl>(std::make_unique<AST::Identifier>(id.literal),
                                             std::move(params),
                                             std::move(body));
    }

    if (m_currToken.type == TokenType::Return) {
        eatToken(TokenType::Return);
        std::unique_ptr<AST::Expr> expr = parseExpr();
        return std::make_unique<AST::ReturnStmt>(std::move(expr));
    }

    // assignment or expr statement
    std::unique_ptr<AST::Expr> expr = parseExpr();
    if (m_currToken.type == TokenType::Equal) {
        eatToken(TokenType::Equal);
        auto rval = parseExpr();
        // TODO: add checks that lval is valid.
        return std::make_unique<AST::AssignStmt>(std::move(expr), std::move(rval));
    } else {
        return std::make_unique<AST::ExprStmt>(std::move(expr));
    }
}


std::unique_ptr<AST::BlockStmt> Parser::parseBlockStmt() {
    eatToken(TokenType::LeftBrace);
    std::vector<std::unique_ptr<AST::Stmt>> statements;
    while (m_currToken.type != TokenType::RightBrace) {
        statements.push_back(parseStmt());
        eatToken(TokenType::EOL);
    }
    eatToken(TokenType::RightBrace);
    return std::make_unique<AST::BlockStmt>(std::move(statements));
}

std::unique_ptr<AST::Expr> Parser::parseExpr() {
    return parseOrExpr();
}

std::unique_ptr<AST::Expr> Parser::parseOrExpr() {
    std::unique_ptr<AST::Expr> expr = parseAndExpr();
    while (m_currToken.type == TokenType::Or) {
        eatToken(m_currToken.type);
        auto right = parseAndExpr();
        expr = std::make_unique<AST::BinaryExpr>(TokenType::Or,
                                                 std::move(expr),
                                                 std::move(right));
    }
    return expr;
}

std::unique_ptr<AST::Expr> Parser::parseAndExpr() {
    std::unique_ptr<AST::Expr> expr = parseEqExpr();
    while (m_currToken.type == TokenType::And) {
        eatToken(m_currToken.type);
        auto right = parseEqExpr();
        expr = std::make_unique<AST::BinaryExpr>(TokenType::And,
                                                 std::move(expr),
                                                 std::move(right));
    }
    return expr;
}

std::unique_ptr<AST::Expr> Parser::parseEqExpr() {
    std::unique_ptr<AST::Expr> expr = parseCompExpr();
    while (m_currToken.type == TokenType::EqualEqual || m_currToken.type == TokenType::BangEqual) {
        TokenType op = m_currToken.type;
        eatToken(m_currToken.type);
        auto right = parseCompExpr();
        expr = std::make_unique<AST::BinaryExpr>(op,
                                                 std::move(expr),
                                                 std::move(right));
    }
    return expr;
}

std::unique_ptr<AST::Expr> Parser::parseCompExpr() {
    std::unique_ptr<AST::Expr> expr = parseConcatExpr();
    while (m_currToken.type == TokenType::GreaterEqual ||
           m_currToken.type == TokenType::LesserEqual ||
           m_currToken.type == TokenType::Greater ||
           m_currToken.type == TokenType::Lesser) {
        TokenType op = m_currToken.type;
        eatToken(m_currToken.type);
        auto right = parseConcatExpr();
        expr = std::make_unique<AST::BinaryExpr>(op,
                                                 std::move(expr),
                                                 std::move(right));
    }
    return expr;
}

std::unique_ptr<AST::Expr> Parser::parseConcatExpr() {
    std::unique_ptr<AST::Expr> expr = parseAddExpr();
    while (m_currToken.type == TokenType::Ampersand) {
        TokenType op = m_currToken.type;
        eatToken(m_currToken.type);
        auto right = parseAddExpr();
        expr = std::make_unique<AST::BinaryExpr>(op,
                                                 std::move(expr),
                                                 std::move(right));
    }
    return expr;
}

std::unique_ptr<AST::Expr> Parser::parseAddExpr() {
    std::unique_ptr<AST::Expr> expr = parseMulExpr();
    while (m_currToken.type == TokenType::Plus || m_currToken.type == TokenType::Minus) {
        TokenType op = m_currToken.type;
        eatToken(m_currToken.type);
        std::unique_ptr<AST::Expr> right = parseMulExpr();
        expr = std::make_unique<AST::BinaryExpr>(op,
                                                 std::move(expr),
                                                 std::move(right));
    }
    return expr;
}

std::unique_ptr<AST::Expr> Parser::parseMulExpr() {
    auto expr = parseUnaryExpr();
    while (m_currToken.type == TokenType::Star || m_currToken.type == TokenType::Slash) {
        TokenType op = m_currToken.type;
        eatToken(m_currToken.type);
        auto right = parseUnaryExpr();
        expr = std::make_unique<AST::BinaryExpr>(op,
                                                 std::move(expr),
                                                 std::move(right));
    }
    return expr;
}

std::unique_ptr<AST::Expr> Parser::parseUnaryExpr() {
    if (m_currToken.type == TokenType::Plus ||
        m_currToken.type == TokenType::Minus ||
        m_currToken.type == TokenType::Bang ||
        m_currToken.type == TokenType::Ampersand) {
        TokenType op = m_currToken.type;
        eatToken(m_currToken.type);
        auto operand = parseUnaryExpr();
        return std::make_unique<AST::UnaryExpr>(op,
                                                std::move(operand));
    } else if (m_currToken.type == TokenType::LeftParen) {
        eatToken(m_currToken.type);
        auto expr = parseExpr();
        eatToken(TokenType::RightParen);
        return expr;
    } else if (m_currToken.type == TokenType::String) {
        std::string lit = m_currToken.literal;
        eatToken(m_currToken.type);
        return std::make_unique<AST::StringLit>(lit);
    } else if (m_currToken.type == TokenType::Integer) {
        std::string lit = m_currToken.literal;
        eatToken(m_currToken.type);
        return std::make_unique<AST::IntegerLit>(lit);
    } else if (m_currToken.type == TokenType::Float) {
        std::string lit = m_currToken.literal;
        eatToken(m_currToken.type);
        return std::make_unique<AST::FloatLit>(lit);
    } else if (m_currToken.type == TokenType::True) {
        eatToken(m_currToken.type);
        return std::make_unique<AST::BooleanLit>(true);
    } else if (m_currToken.type == TokenType::False) {
        eatToken(m_currToken.type);
        return std::make_unique<AST::BooleanLit>(false);
    } else if (m_currToken.type == TokenType::Identifier) {
        auto id = std::make_unique<AST::Identifier>(m_currToken.literal);
        eatToken(m_currToken.type);
        if (m_currToken.type == TokenType::LeftParen) {
            // function call
            std::vector<std::unique_ptr<AST::Expr>> args;
            eatToken(m_currToken.type);
            while (m_currToken.type != TokenType::RightParen) {
                auto arg = parseExpr();
                if (m_currToken.type != TokenType::RightParen) {
                    eatToken(TokenType::Comma);
                }
                args.push_back(std::move(arg));
            }
            return std::make_unique<AST::FnCall>(std::move(id), std::move(args));
        }
        return static_cast<std::unique_ptr<AST::Expr>>(std::move(id));
    }
    return nullptr;
}
