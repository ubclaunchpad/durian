#pragma once

namespace AST {
    // hacky way around C++ limitations
    struct Stmt;
    struct BlockStmt;
    struct IfStmt;
    struct WhileStmt;
    struct NextStmt;
    struct BreakStmt;
    struct LetStmt;
    struct AssignStmt;
    struct PrintStmt;
    struct ErrStmt;
    struct ScanStmt;
    struct FnDecl;
    struct ReturnStmt;
    struct Expr;
    struct BinaryExpr;
    struct UnaryExpr;
    struct IntegerLit;
    struct FloatLit;
    struct StringLit;
    struct BooleanLit;
    struct Identifier;
    struct FnCall;
    struct ExprStmt;
}

class Visitor {
public:
    virtual void visit(AST::AssignStmt *node) = 0;
    virtual void visit(AST::BinaryExpr *node) = 0;
    virtual void visit(AST::BlockStmt *node) = 0;
    virtual void visit(AST::BooleanLit *node) = 0;
    virtual void visit(AST::BreakStmt *node) = 0;
    virtual void visit(AST::ErrStmt *node) = 0;
    virtual void visit(AST::ExprStmt *node) = 0;
    virtual void visit(AST::FloatLit *node) = 0;
    virtual void visit(AST::FnCall *node) = 0;
    virtual void visit(AST::FnDecl *node) = 0;
    virtual void visit(AST::Identifier *node) = 0;
    virtual void visit(AST::IfStmt *node) = 0;
    virtual void visit(AST::IntegerLit *node) = 0;
    virtual void visit(AST::LetStmt *node) = 0;
    virtual void visit(AST::NextStmt *node) = 0;
    virtual void visit(AST::PrintStmt *node) = 0;
    virtual void visit(AST::ReturnStmt *node) = 0;
    virtual void visit(AST::ScanStmt *node) = 0;
    virtual void visit(AST::StringLit *node) = 0;
    virtual void visit(AST::UnaryExpr *node) = 0;
    virtual void visit(AST::WhileStmt *node) = 0;
};