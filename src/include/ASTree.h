#pragma once

#include <Token.h>
#include <vector>

enum struct StatementType {
    Function,
    FunctionCall,

    // todo
};

struct Statement {
    StatementType m_type;
};

class ASTree {
    std::vector<std::unique_ptr<Statement>> m_statements;

};

//////////////////////////////////////////
/// Functions

struct Function : Statement {
    std::string name;
    std::vector<std::unique_ptr<Statement>> body;
};

struct FunctionCall : Statement {
    std::string name;
    std::shared_ptr<Function> function;
    std::vector<std::unique_ptr<Statement>> args;
};

//////////////////////////////////////////
/// General operators

struct GeneralOperator : Statement {
    std::unique_ptr<Statement> left;
    std::unique_ptr<Statement> right;
    /// etc....
};

struct Addition : GeneralOperator {
    std::string name;
    std::unique_ptr<Statement> left;
    std::unique_ptr<Statement> right;
};

//////////////////////////////////////////
/// Control flow operators

struct ControlFlowOperator : Statement {

};

struct Return : ControlFlowOperator {
    std::unique_ptr<Statement> value;
};

//////////////////////////////////////////
/// Literals

struct Integer : Statement {
    std::string name;
    int integer;
};

struct String : Statement {
    std::string name;
    std::string value;
};
