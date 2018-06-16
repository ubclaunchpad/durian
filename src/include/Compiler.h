#pragma once

#include <Parser.h>
#include <ASTree.h>

class Compiler {
    Parser m_parser;
    std::vector<unsigned char> m_bytecode;
public:
    explicit Compiler(Parser parser);
private:
    void visit(AST::AssignStmt *node);
    void visit(AST::BinaryExpr *node);
    void visit(AST::BlockStmt *node);
    void visit(AST::BooleanLit *node);
    void visit(AST::BreakStmt *node);
    void visit(AST::ErrStmt *node);
    void visit(AST::ExprStmt *node);
    void visit(AST::FloatLit *node);
    void visit(AST::FnCall *node);
    void visit(AST::FnDecl *node);
    void visit(AST::Identifier *node);
    void visit(AST::IfStmt *node);
    void visit(AST::LetStmt *node);
    void visit(AST::NextStmt *node);
    void visit(AST::PrintStmt *node);
    void visit(AST::ReturnStmt *node);
    void visit(AST::ScanStmt *node);
    void  visit(AST::StringLit *node);
    void visit(AST::UnaryExpr *node);
    void visit(AST::WhileStmt *node);
};