#include <Parser.h>

Parser::Parser(const std::string input)
    : m_lexer(input)
    , m_currentToken(m_lexer.getToken())
{

}

void Parser::buildTree() {
    parseStatement();
}

std::unique_ptr<Statement> Parser::parseStatement() {

}

std::unique_ptr<Expression> Parser::parseExpression() {

}

std::unique_ptr<Literal> Parser::parseLiteral() {
    std::unique_ptr<Literal> statement;
    switch (m_currentToken.type) {
        case TokenType::Integer:
            statement = std::make_unique<Integer>(
                    Integer(m_currentToken.literal));
            break;
        case TokenType::Float:
            statement = std::make_unique<Float>(
                    Float(m_currentToken.literal));
            break;
        case TokenType::String:
            statement = std::make_unique<String>(
                    String(m_currentToken.literal));
            break;
        case TokenType::True:
        case TokenType::False:
            statement = std::make_unique<Boolean>(
                    Boolean(m_currentToken.literal));
            break;
        default:
            // todo : exceptions, details
            printf("your token is shit");
    }
    getNextToken();
    return std::move(statement);
}

std::unique_ptr<Function> Parser::parseFunction() {

}

std::unique_ptr<Return> Parser::parseReturn() {

}

