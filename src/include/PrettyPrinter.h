#pragma once

#include <Visitor.h>

#include <string>

class PrettyPrinter : public Visitor {
public:
    PrettyPrinter() = default;
    void visit(AST::AssignStmt *node) override;
    void visit(AST::BinaryExpr *node) override;
    void visit(AST::BlockStmt *node) override;
    void visit(AST::BooleanLit *node) override;
    void visit(AST::BreakStmt *node) override;
    void visit(AST::ErrStmt *node) override;
    void visit(AST::ExprStmt *node) override;
    void visit(AST::FloatLit *node) override;
    void visit(AST::FnCall *node) override;
    void visit(AST::FnDecl *node) override;
    void visit(AST::Identifier *node) override;
    void visit(AST::IfStmt *node) override;
    void visit(AST::IntegerLit *node) override;
    void visit(AST::LetStmt *node) override;
    void visit(AST::NextStmt *node) override;
    void visit(AST::PrintStmt *node) override;
    void visit(AST::ReturnStmt *node) override;
    void visit(AST::ScanStmt *node) override;
    void visit(AST::StringLit *node) override;
    void visit(AST::UnaryExpr *node) override;
    void visit(AST::WhileStmt *node) override;
};

