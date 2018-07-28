#include <array>
#include <cstring>

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
    std::array<unsigned char, sizeof(double)> tmp = {};
    memcpy(tmp.data(), &node->m_value, sizeof(double));
    m_buffer.push_back(Opcode::DCONST);
    for (unsigned char val : tmp) {
        m_buffer.push_back(val);
    }
}

void Compiler::visit(AST::FnCall *node) {}

void Compiler::visit(AST::FnDecl *node) {}

void Compiler::visit(AST::Identifier *node) {}

void Compiler::visit(AST::IfStmt *node) {}

void Compiler::visit(AST::IntegerLit *node) {
    std::array<unsigned char, sizeof(double)> tmp = {};
    memcpy(tmp.data(), &node->m_value, sizeof(int64_t));
    m_buffer.push_back(Opcode::ICONST);
    for (unsigned char val : tmp) {
        m_buffer.push_back(val);
    }
}

void Compiler::visit(AST::LetStmt *node) {}

void Compiler::visit(AST::NextStmt *node) {}

void Compiler::visit(AST::PrintStmt *node) {
    node->m_expr->accept(this);
    m_buffer.push_back(Opcode::PRINT);
}

void Compiler::visit(AST::ReturnStmt *node) {}

void Compiler::visit(AST::ScanStmt *node) {}

void Compiler::visit(AST::StringLit *node) {
    const std::string lit = node->m_value;

    std::array<uint8_t, sizeof(uint64_t)> tmp = {};
    uint64_t idx;
    if (m_staticStringMap.find(lit) == m_staticStringMap.end()) {
        // string not present in static data, add
        idx = m_currStaticStringIndex;
        std::array<uint8_t, sizeof(uint64_t)> tmpStr = {};
        std::memcpy(tmpStr.data(), lit.data(), lit.size());
        for (auto val : tmpStr) {
            m_staticStrings.push_back(val);
        }
        m_staticStringMap.insert({lit, m_currStaticStringIndex});
        m_currStaticStringIndex += lit.size();
    } else {
        idx = m_staticStringMap.at(lit);
    }
    std::memcpy(tmp.data(), &idx, sizeof(uint64_t));
    for (auto val : tmp) {
        m_buffer.push_back(val);
    }
    m_buffer.push_back(Opcode::NEWSTR8);
}

void Compiler::visit(AST::UnaryExpr *node) {
    node->m_operand->accept(this);
    m_buffer.push_back(getUnOpcode(node->m_op));
}

void Compiler::visit(AST::WhileStmt *node) {}