#pragma once

#include <unordered_map>

#include <Parser.h>
#include <ASTree.h>
#include <Visitor.h>

class Compiler : public Visitor {
    std::vector<unsigned char> m_buffer;
    std::vector<unsigned char> m_header;
    std::vector<uint8_t> m_staticStrings;
    std::unordered_map<std::string, uint32_t> m_staticStringMap;
    uint32_t m_currStaticStringIndex;
public:
    std::vector<unsigned char> getBuffer() { return m_buffer; }
    std::vector<uint8_t> getStaticStrings() { return m_staticStrings; };
    virtual void visit(AST::AssignStmt *node) override;
    virtual void visit(AST::BinaryExpr *node) override;
    virtual void visit(AST::BlockStmt *node) override;
    virtual void visit(AST::BooleanLit *node) override;
    virtual void visit(AST::BreakStmt *node) override;
    virtual void visit(AST::ErrStmt *node) override;
    virtual void visit(AST::ExprStmt *node) override;
    virtual void visit(AST::FloatLit *node) override;
    virtual void visit(AST::FnCall *node) override;
    virtual void visit(AST::FnDecl *node) override;
    virtual void visit(AST::Identifier *node) override;
    virtual void visit(AST::IfStmt *node) override;
    virtual void visit(AST::IntegerLit *node) override;
    virtual void visit(AST::LetStmt *node) override;
    virtual void visit(AST::NextStmt *node) override;
    virtual void visit(AST::PrintStmt *node) override;
    virtual void visit(AST::ReturnStmt *node) override;
    virtual void visit(AST::ScanStmt *node) override;
    virtual void visit(AST::StringLit *node) override;
    virtual void visit(AST::UnaryExpr *node) override;
    virtual void visit(AST::WhileStmt *node) override;
};