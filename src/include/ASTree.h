#pragma once

#include <Token.h>
#include <vector>
#include <ios>
#include <sstream>

struct Statement { };

class ASTree {
    std::vector<std::unique_ptr<Statement>> m_statements;
};

//////////////////////////////////////////
/// Expressions

struct Expression : public Statement { };

class ExpressionGroup : public Expression {
    std::unique_ptr<Expression> m_expression;
public:
    explicit ExpressionGroup(std::unique_ptr<Expression> expression)
            : m_expression(std::move(expression)) { }
};

class BinaryExpression : public Expression {
    char m_op;
    std::unique_ptr<ExpressionGroup> m_left;
    std::unique_ptr<ExpressionGroup> m_right;
public:
    BinaryExpression(char op, std::unique_ptr<ExpressionGroup> left,
                     std::unique_ptr<ExpressionGroup> right)
            : m_op(op)
            , m_left(std::move(left))
            , m_right(std::move(right)) { }
};

class UnaryExpression : public Expression {
    char m_op;
    std::unique_ptr<ExpressionGroup> m_operand;
public:
    UnaryExpression(char op, std::unique_ptr<ExpressionGroup> operand)
            : m_op(op)
            , m_operand(std::move(operand)) { }
};

class FunctionCall : public Expression {
    std::string m_functionName;
    std::vector<std::unique_ptr<ExpressionGroup>> m_args;
public:
    FunctionCall(std::string &functionName,
                 std::vector<std::unique_ptr<ExpressionGroup>> args)
            : m_functionName(functionName)
            , m_args(std::move(args)) { }
};

//////////////////////////////////////////
/// Literals

class Literal : public Expression { };

class Integer : public Literal {
    int m_value;
public:
    explicit Integer(std::string value) : m_value(std::stoi(value)) { }
};

class Float : public Literal {
    float m_value;
public:
    explicit Float(std::string value) : m_value(std::stof(value)) { }
};

class String : public Literal {
    std::string m_value;
public:
    explicit String(std::string value) : m_value(std::move(value)) { }
};

class Boolean : public Literal {
    bool m_value;
public:
    explicit Boolean(std::string value) {
        std::istringstream(value) >> std::boolalpha >> m_value;
    }
};

//////////////////////////////////////////
/// Functions

class Function : public Statement {
    std::string m_name;
    std::vector<std::string> m_argNames;
    std::unique_ptr<Statement> m_block;
public:
    Function(std::string &name, std::vector<std::string> argNames,
             std::unique_ptr<Statement> block)
            : m_name(name)
            , m_argNames(std::move(argNames))
            , m_block(std::move(block)) { }
};

class Return : public Statement {
    std::unique_ptr<Expression> m_expression;
public:
    explicit Return(std::unique_ptr<Expression> expression)
        : m_expression(std::move(expression)) { }
};
