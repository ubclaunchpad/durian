#pragma once

#include <Lexer.h>
#include <ASTree.h>
#include <exception>

class Parser {
    Lexer m_lexer;
    Token m_currentToken;

public:
    explicit Parser(Lexer lexer);
    void buildTree();
private:
    Token getNextToken() {
        return m_currentToken = m_lexer.getToken();
    }
    // Parsers
    std::unique_ptr<Statement> parseStatement();
    // Expressions
    std::unique_ptr<Expression> parseExpression();
    std::unique_ptr<Literal> parseLiteral();
    // Basic statements
    std::unique_ptr<Function> parseFunction();
    std::unique_ptr<Return> parseReturn();
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
