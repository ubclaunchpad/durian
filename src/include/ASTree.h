#pragma once

#include <Token.h>
#include <vector>
#include <ios>
#include <sstream>
#include <memory>

struct Statement { };

//////////////////////////////////////////
/// Expressions

struct Expression : public Statement { };

struct ExpressionGroup : public Expression {
    std::unique_ptr<Expression> m_expression;
public:
    explicit ExpressionGroup(std::unique_ptr<Expression> expression)
            : m_expression(std::move(expression)) { }
};

struct BinaryExpression : public Expression {
    TokenType m_op;
    std::unique_ptr<Expression> m_left;
    std::unique_ptr<Expression> m_right;
public:
    BinaryExpression(TokenType op, std::unique_ptr<Expression> left,
                     std::unique_ptr<Expression> right)
            : m_op(op)
            , m_left(std::move(left))
            , m_right(std::move(right)) { }
};

struct UnaryExpression : public Expression {
    TokenType m_op;
    std::unique_ptr<Expression> m_operand;
public:
    UnaryExpression(TokenType op, std::unique_ptr<Expression> operand)
            : m_op(op)
            , m_operand(std::move(operand)) { }
};

struct FunctionCall : public Expression {
    std::string m_functionName;
    std::vector<std::unique_ptr<Expression>> m_args;
public:
    FunctionCall(std::string &functionName,
                 std::vector<std::unique_ptr<Expression>> args)
            : m_functionName(functionName)
            , m_args(std::move(args)) { }
};

struct Variable : public Expression {
    std::string m_name;
public:
    Variable(const std::string &name) : m_name(name) { }
};

//////////////////////////////////////////
/// Literals

struct Literal : public Expression { };

struct Integer : public Literal {
    int m_value;
public:
    explicit Integer(const std::string &value) : m_value(std::stoi(value)) { }
};

struct Float : public Literal {
    float m_value;
public:
    explicit Float(const std::string &value) : m_value(std::stof(value)) { }
};

struct String : public Literal {
    std::string m_value;
public:
    explicit String(const std::string &value) : m_value(value) { }
};

struct Boolean : public Literal {
    bool m_value;
public:
    explicit Boolean(const std::string &value) {
        std::istringstream(value) >> std::boolalpha >> m_value;
    }
};

//////////////////////////////////////////
/// Functions

struct Function : public Statement {
    std::string m_name;
    std::vector<std::string> m_argNames;
    std::vector<std::unique_ptr<Statement>> m_statements;
public:
    Function(std::string &name, std::vector<std::string> argNames,
             std::vector<std::unique_ptr<Statement>> statements)
            : m_name(name)
            , m_argNames(std::move(argNames))
            , m_statements(std::move(statements)) { }
};

struct Return : public Statement {
    std::unique_ptr<Expression> m_expression;
public:
    explicit Return(std::unique_ptr<Expression> expression)
        : m_expression(std::move(expression)) { }
};
