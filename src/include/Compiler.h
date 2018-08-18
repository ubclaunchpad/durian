#pragma once

#include <unordered_map>

#include <ASTree.h>
#include <Parser.h>
#include <Types.h>
#include <Visitor.h>

class Compiler : public Visitor {
    std::vector<Bytecode> m_buffer;
    std::vector<Bytecode> m_header;
    std::vector<Bytecode> m_staticStrings;
    std::unordered_map<std::string, BytecodeIndex> m_staticStringMap;
    BytecodeIndex m_currStaticStringIndex;
public:
    std::vector<Bytecode> getBuffer() { return m_buffer; }
    std::vector<Bytecode> getStaticStrings() { return m_staticStrings; };
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