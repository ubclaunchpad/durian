#include <PrettyPrinter.h>

#include <Token.h>

#include <iostream>
#include <ASTree.h>

void PrettyPrinter::PrettyPrinter::visit(AST::AssignStmt *node) {
    std::cout << "assign ";
    node->m_ident->accept(this);
    std::cout << " to ";
    node->m_expr->accept(this);
    std::cout << ";" << std::endl;
}

void PrettyPrinter::visit(AST::BinaryExpr *node) {
    std::cout << "(";
    std::cout << tokTypeToString(node->m_op) << " ";
    node->m_left->accept(this);
    std::cout << " ";
    node->m_right->accept(this);
    std::cout << ")";
};

void PrettyPrinter::visit(AST::BlockStmt *node) {
    std::cout << "{" << std::endl;
    for (auto iter = node->m_statements.cbegin(); iter != node->m_statements.cend(); ++iter) {
        std::cout << "    ";
        iter->get()->accept(this);
    }
    std::cout << "};" << std::endl;
};

void PrettyPrinter::visit(AST::BooleanLit *node) {
    if (node->m_value) {
        std::cout << "(literal True)";
    } else {
        std::cout << "(literal False)";
    }
};

void PrettyPrinter::visit(AST::BreakStmt *node) {
    std::cout << "break;" << std::endl;
};

void PrettyPrinter::visit(AST::ErrStmt *node) {
    std::cout << "err ";
    node->m_expr->accept(this);
    std::cout << ";" << std::endl;
};

void PrettyPrinter::visit(AST::ExprStmt *node) {
    node->m_expr->accept(this);
    std::cout << ";" << std::endl;
};

void PrettyPrinter::visit(AST::FloatLit *node) {
    std::cout << "(literal " << node->m_value << ")";
};

void PrettyPrinter::visit(AST::FnCall *node) {
    std::cout << "(call ";
    node->m_ident->accept(this);
    std::cout << " with args ";
    for (auto iter = node->m_args.cbegin(); iter != node->m_args.cend(); ++iter) {
        iter->get()->accept(this);
    }
    std::cout << ")";
};

void PrettyPrinter::visit(AST::FnDecl *node) {
    std::cout << "define ";
    node->m_ident->accept(this);
    std::cout << " with params ";
    for (auto iter = node->m_params.cbegin(); iter != node->m_params.cend(); ++iter) {
        iter->get()->accept(this);
    }
    std::cout << " and body ";
    node->m_body->accept(this);
    std::cout << ";" << std::endl;
};

void PrettyPrinter::visit(AST::Identifier *node) {
    std::cout << "(ident " << node->m_identStr << ")";
};

void PrettyPrinter::visit(AST::IfStmt *node) {
    std::cout << "if ";
    node->m_condition->accept(this);
    std::cout << " do ";
    node->m_trueBody->accept(this);
    std::cout << "else do ";
    if (node->m_falseBody == nullptr) {
        std:: cout << "nothing;" << std::endl;
    } else {
        node->m_falseBody->accept(this);
    }
};

void PrettyPrinter::visit(AST::IntegerLit *node) {
    std::cout << "(literal " << node->m_value << ")";
};

void PrettyPrinter::visit(AST::LetStmt *node) {
    std::cout << "let ";
    node->m_ident->accept(this);
    std::cout << " be ";
    node->m_expr->accept(this);
    std::cout << ";" << std::endl;
};

void PrettyPrinter::visit(AST::NextStmt *node) {
    std::cout << "next;" << std::endl;
};

void PrettyPrinter::visit(AST::PrintStmt *node) {
    std::cout << "print ";
    node->m_expr->accept(this);
    std::cout << ";" << std::endl;
};

void PrettyPrinter::visit(AST::ReturnStmt *node) {
    std::cout << "return;" << std::endl;
};

void PrettyPrinter::visit(AST::ScanStmt *node) {
    std::cout << "scan ";
    node->m_ident->accept(this);
    std::cout << ";" << std::endl;
};

void PrettyPrinter::visit(AST::StringLit *node) {
    std::cout << "(literal " << node->m_value << ")";
};

void PrettyPrinter::visit(AST::UnaryExpr *node) {
    std::cout << "(";
    std::cout << tokTypeToString(node->m_op) << " ";
    node->m_operand->accept(this);
    std::cout << ")";
};

void PrettyPrinter::visit(AST::WhileStmt *node) {
    std::cout << "while ";
    node->m_condition->accept(this);
    std::cout << " do ";
    node->m_body->accept(this);
};
