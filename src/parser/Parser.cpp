#include <Parser.h>

Parser::Parser(Lexer lexer)
    : m_lexer(std::move(lexer))
    , m_currentToken(m_lexer.getToken())
{

}

void Parser::buildTree() {
    parseStatement();
}

std::unique_ptr<AST::Stmt> Parser::parseStatement() {
    std::unique_ptr<AST::Stmt> statement;
    Token identifier;
    switch(m_currentToken.type) {
        case TokenType::Def:
            statement = parseFunction();
        case TokenType::Return:
            statement = parseReturn();
        case TokenType::Identifier:
            identifier = m_currentToken;
            getNextToken();
            switch(m_currentToken.type) {
                case TokenType::LeftParen:
                    getNextToken();
            }
            break;

        // todo: other statements

        default:
            statement = parseExpression();
    }
    getNextToken();
    return std::move(statement);
}

std::unique_ptr<AST::Expr> Parser::parseExpression() {
    std::unique_ptr<AST::Expr> statement;
    switch(m_currentToken.type) {
        // Check for group
        case TokenType::LeftParen:
            getNextToken();
            break;
        case TokenType::RightParen:
            // todo ummmm
            statement = std::unique_ptr<AST::Expr>(nullptr);
            break;

        // If operator first, this is an unary expression
        case TokenType::Plus:
        case TokenType::Minus:
        case TokenType::Ampersand:
        case TokenType::Bang:
        // TODO
        default:
            // Check for literal - if no literal, just return null
            statement = parseLiteral();
            if (!statement) break;
            // Check for operator
            switch(m_currentToken.type) {
                case TokenType::Plus:
                case TokenType::Minus:
                case TokenType::Star:
                case TokenType::Slash:
                case TokenType::Ampersand:
                case TokenType::Lesser:
                case TokenType::LesserEqual:
                case TokenType::Greater:
                case TokenType::GreaterEqual:
                case TokenType::Equal:
                case TokenType::EqualEqual:
                case TokenType::BangEqual:
                case TokenType::And:
                case TokenType::Or:
                default:
                    // Otherwise return literal
                    break;
            }
    }
    getNextToken();
    return std::move(statement);
}

std::unique_ptr<AST::Expr> Parser::parseLiteral() {
    std::unique_ptr<AST::Expr> statement;
    switch (m_currentToken.type) {
        case TokenType::Integer:
            statement = util::make_unique<AST::IntegerLit>(
                    AST::IntegerLit(m_currentToken.literal));
            break;
        case TokenType::Float:
            statement = util::make_unique<AST::FloatLit>(
                    AST::FloatLit(m_currentToken.literal));
            break;
        case TokenType::String:
            statement = util::make_unique<AST::StringLit>(
                    AST::StringLit(m_currentToken.literal));
            break;
        case TokenType::True:
        case TokenType::False:
            statement = util::make_unique<AST::BooleanLit>(
                    AST::BooleanLit(m_currentToken.literal));
            break;
        default:
            // todo : exceptions, details
            return std::unique_ptr<AST::Expr>(nullptr);
    }
    getNextToken();
    return std::move(statement);
}

std::unique_ptr<AST::FnDecl> Parser::parseFunction() {
    return std::unique_ptr<AST::FnDecl>(nullptr);
}

std::unique_ptr<AST::ReturnStmt> Parser::parseReturn() {
    return std::unique_ptr<AST::ReturnStmt>(nullptr);
}

