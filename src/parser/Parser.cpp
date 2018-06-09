#include <Parser.h>

Parser::Parser(Lexer lexer)
    : m_lexer(std::move(lexer))
    , m_currentToken(m_lexer.getToken())
{

}

void Parser::buildTree() {
    parseStatement();
}

std::unique_ptr<Statement> Parser::parseStatement() {
    std::unique_ptr<Statement> statement;
    switch(m_currentToken.type) {
        case TokenType::Def:
            statement = parseFunction();
        case TokenType::Return:
            statement = parseReturn();
        case TokenType::Identifier:
            Token identifier = m_currentToken;
            getNextToken();
            switch(m_currentToken.type) {
                case TokenType::LeftParen:
                    getNextToken();
                default:
                    statement = util::make_unique<Variable>(
                            m_currentToken.literal);
            }
            break;

        // todo: other statements

        default:
            statement = parseExpression();
    }
    getNextToken();
    return std::move(statement);
}

std::unique_ptr<Expression> Parser::parseExpression() {
    std::unique_ptr<Expression> statement;
    switch(m_currentToken.type) {
        // Check for group
        case TokenType::LeftParen:
            getNextToken();
            statement = util::make_unique<ExpressionGroup>(
                    parseExpression());
            break;
        case TokenType::RightParen:
            // todo ummmm
            statement = std::unique_ptr<Literal>(nullptr);
            break;

        // If operator first, this is an unary expression
        case TokenType::Plus:
        case TokenType::Minus:
        case TokenType::Ampersand:
        case TokenType::Bang:
            statement = util::make_unique<UnaryExpression>(
                    m_currentToken.type, parseExpression());

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
                    // If operator, build BinaryExpression
                    statement = util::make_unique<BinaryExpression>(
                            m_currentToken.type, statement, parseExpression());
                default:
                    // Otherwise return literal
                    break;
            }
    }
    getNextToken();
    return std::move(statement);
}

std::unique_ptr<Literal> Parser::parseLiteral() {
    std::unique_ptr<Literal> statement;
    switch (m_currentToken.type) {
        case TokenType::Integer:
            statement = util::make_unique<Integer>(
                    Integer(m_currentToken.literal));
            break;
        case TokenType::Float:
            statement = util::make_unique<Float>(
                    Float(m_currentToken.literal));
            break;
        case TokenType::String:
            statement = util::make_unique<String>(
                    String(m_currentToken.literal));
            break;
        case TokenType::True:
        case TokenType::False:
            statement = util::make_unique<Boolean>(
                    Boolean(m_currentToken.literal));
            break;
        default:
            // todo : exceptions, details
            return std::unique_ptr<Literal>(nullptr);
    }
    getNextToken();
    return std::move(statement);
}

std::unique_ptr<Function> Parser::parseFunction() {
    return std::unique_ptr<Function>(nullptr);
}

std::unique_ptr<Return> Parser::parseReturn() {
    return std::unique_ptr<Return>(nullptr);
}

