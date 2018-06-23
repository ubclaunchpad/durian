#pragma once

#include <Parser.h>
#include <ASTree.h>

class Visitor {
private:
    void visit(AST::AssignStmt *node) = 0;
    void visit(AST::BinaryExpr *node) = 0;
    void visit(AST::BlockStmt *node) = 0;
    void visit(AST::BooleanLit *node) = 0;
    void visit(AST::BreakStmt *node) = 0;
    void visit(AST::ErrStmt *node) = 0;
    void visit(AST::ExprStmt *node) = 0;
    void visit(AST::FloatLit *node) = 0;
    void visit(AST::FnCall *node) = 0;
    void visit(AST::FnDecl *node) = 0;
    void visit(AST::Identifier *node) = 0;
    void visit(AST::IfStmt *node) = 0;
    void visit(AST::LetStmt *node) = 0;
    void visit(AST::NextStmt *node) = 0;
    void visit(AST::PrintStmt *node) = 0;
    void visit(AST::ReturnStmt *node) = 0;
    void visit(AST::ScanStmt *node) = 0;
    void  visit(AST::StringLit *node) = 0;
    void visit(AST::UnaryExpr *node) = 0;
    void visit(AST::WhileStmt *node) = 0;
};