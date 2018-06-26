#include <Compiler.h>

Compiler::Compiler(Parser parser) : m_parser(parser) {}

void Compiler::visit(AST::AssignStmt *node);

void Compiler::visit(AST::BinaryExpr *node) {
    visit(node->m_right);
    visit(node->m_left);
    m_buffer.push_back(node->m_op.getBinOpcode());
}

void Compiler::visit(AST::BlockStmt *node);

void Compiler::visit(AST::BooleanLit *node) {
    m_buffer.push_back(node->m_value ? Opcode::BCONST_T : Opcode::BCONST_F);
}

void Compiler::visit(AST::BreakStmt *node);

void Compiler::visit(AST::ErrStmt *node);

void Compiler::visit(AST::ExprStmt *node) {
    visit(node->m_expr);
}

void Compiler::visit(AST::FloatLit *node) {
    char tmp[sizeof(double)] = reinterpret_cast<unsigned char*>(&node->m_value);
    m_buffer.push_back(Opcode::DCONST);
    for (int i = 0; i < sizeof(double); i++) m_buffer.push_back(tmp[i]);
}

void Compiler::visit(AST::FnCall *node);

void Compiler::visit(AST::FnDecl *node);

void Compiler::visit(AST::Identifier *node);

void Compiler::visit(AST::IfStmt *node);

void Compiler::visit(AST::IntegerLit *node) {
    char tmp[sizeof(int64_t)] = reinterpret_cast<unsigned char*>(&node->m_value);
    m_buffer.push_back(Opcode::ICONST);
    for (int i = 0; i < sizeof(int64_t); i++) m_buffer.push_back(tmp[i]);
}

void Compiler::visit(AST::LetStmt *node);

void Compiler::visit(AST::NextStmt *node);

void Compiler::visit(AST::PrintStmt *node);

void Compiler::visit(AST::ReturnStmt *node);

void Compiler::visit(AST::ScanStmt *node);

void Compiler::visit(AST::StringLit *node);

void Compiler::visit(AST::UnaryExpr *node) {
    visit(node->m_operand);
    m_buffer.push_back(node->m_op.getUnOpcode());
}

void Compiler::visit(AST::WhileStmt *node);