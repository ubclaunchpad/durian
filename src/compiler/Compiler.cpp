#include <Compiler.h>

Compiler::Compiler(Parser parser) : m_parser(parser) {}

void Compiler::visit(AST::AssignStmt *node);
void Compiler::visit(AST::BinaryExpr *node) {
    visit(node->m_right);
    visit(node->m_left);
    m_buffer.push_back(node->m_op);
}
void Compiler::visit(AST::BlockStmt *node);
void Compiler::visit(AST::BooleanLit *node);
void Compiler::visit(AST::BreakStmt *node);
void Compiler::visit(AST::ErrStmt *node);
void Compiler::visit(AST::ExprStmt *node) {
    visit(node->m_expr);
}
void Compiler::visit(AST::FloatLit *node);
void Compiler::visit(AST::FnCall *node);
void Compiler::visit(AST::FnDecl *node);
void Compiler::visit(AST::Identifier *node);
void Compiler::visit(AST::IfStmt *node);
void Compiler::visit(AST::LetStmt *node);
void Compiler::visit(AST::NextStmt *node);
void Compiler::visit(AST::PrintStmt *node);
void Compiler::visit(AST::ReturnStmt *node);
void Compiler::visit(AST::ScanStmt *node);
void Compiler::visit(AST::StringLit *node);
void Compiler::visit(AST::UnaryExpr *node);
void Compiler::visit(AST::WhileStmt *node);