#include <Compiler.h>

void Compiler::visit(AST::AssignStmt *node) {}

void Compiler::visit(AST::BinaryExpr *node) {
    node->m_left->accept(this);
    node->m_right->accept(this);
    m_buffer.push_back(getBinOpcode(node->m_op));
}

void Compiler::visit(AST::BlockStmt *node) {}

void Compiler::visit(AST::BooleanLit *node) {
    m_buffer.push_back(node->m_value ? Opcode::BCONST_T : Opcode::BCONST_F);
}

void Compiler::visit(AST::BreakStmt *node) {}

void Compiler::visit(AST::ErrStmt *node) {
    node->m_expr->accept(this);
    m_buffer.push_back(Opcode::ERR);
}

void Compiler::visit(AST::ExprStmt *node) {
    node->m_expr->accept(this);
    m_buffer.push_back(Opcode::POP);
}

void Compiler::visit(AST::FloatLit *node) {
    char tmp[sizeof(double)];
    memcpy(tmp, &node->m_value, sizeof(double));
    m_buffer.push_back(Opcode::DCONST);
    for (int i = 0; i < sizeof(double); i++) m_buffer.push_back(tmp[i]);
}

void Compiler::visit(AST::FnCall *node) {}

void Compiler::visit(AST::FnDecl *node) {}

void Compiler::visit(AST::Identifier *node) {}

void Compiler::visit(AST::IfStmt *node) {}

void Compiler::visit(AST::IntegerLit *node) {
    char tmp[sizeof(int64_t)];
    memcpy(tmp, &node->m_value, sizeof(int64_t));
    m_buffer.push_back(Opcode::ICONST);
    for (int i = 0; i < sizeof(int64_t); i++) m_buffer.push_back(tmp[i]);
}

void Compiler::visit(AST::LetStmt *node) {}

void Compiler::visit(AST::NextStmt *node) {}

void Compiler::visit(AST::PrintStmt *node) {
    node->m_expr->accept(this);
    m_buffer.push_back(Opcode::PRINT);
}

void Compiler::visit(AST::ReturnStmt *node) {}

void Compiler::visit(AST::ScanStmt *node) {}

void Compiler::visit(AST::StringLit *node) {}

void Compiler::visit(AST::UnaryExpr *node) {
    node->m_operand->accept(this);
    m_buffer.push_back(getUnOpcode(node->m_op));
}

void Compiler::visit(AST::WhileStmt *node) {}