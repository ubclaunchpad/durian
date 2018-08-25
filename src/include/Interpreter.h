#pragma once

#include <unordered_map>
#include <stack>

#include <Visitor.h>
#include <string>

class Interpreter : public Visitor {

    enum struct DurianType {
        Double,
        Integer,
        Boolean,
        String,
        Function
    };

    struct DurianObject {
        DurianType type;

        union {
            double dval;
            int64_t ival;
            bool bval;
            char sval[1024];
        } value;

        explicit DurianObject(double dval) : type(DurianType::Double) {
            value.dval = dval;
        }

        explicit DurianObject(int64_t ival) : type(DurianType::Integer) {
            value.ival = ival;
        }

        explicit DurianObject(bool bval) : type(DurianType::Boolean) {
            value.bval = bval;
        }

        explicit DurianObject(const std::string &sval) : type(DurianType::String) {
            memcpy(value.sval, sval.data(), 1024);
        }

        bool isTruthy() const { return type != DurianType::Boolean || value.bval; };
    };

    struct BindingException : public std::runtime_error {
        explicit BindingException(const std::string &msg)
                : std::runtime_error(msg) {}
    };

    struct ControlFlowException : public std::exception {
    };

    struct BreakException : public ControlFlowException {
    };

    struct NextException : public ControlFlowException {
    };

    struct ReturnException : public ControlFlowException {
        DurianObject val;

        explicit ReturnException(DurianObject val) : val(val) {}
    };

    class Environment {
        std::unordered_map<std::string, DurianObject> env;
        std::shared_ptr<Environment> parent;
    public:
        Environment() : env(), parent(nullptr) {}

        Environment(std::shared_ptr<Environment> env) : env(), parent(env) {}

        DurianObject get(const std::string &ident) {
            auto find = env.find(ident);
            if (find != env.end()) {
                return find->second;
            } else {
                if (parent != nullptr) {
                    return parent->get(ident);
                }
            }
            throw BindingException("Undeclared identifier " + ident);
        }

        void declare(const std::string &ident, DurianObject initializer) {
            env.insert({ident, initializer});
        }

        void assign(const std::string &ident, DurianObject val) {
            auto find = env.find(ident);
            if (find != env.end()) {
                // TODO I suspect this doesn't work how I think it does
                find->second = val;
            } else {
                if (parent != nullptr) {
                    return parent->assign(ident, val);
                }
            }
            throw BindingException("Undeclared identifier " + ident);
        }
    };

    std::shared_ptr<Environment> m_currentScope;

    std::stack<DurianObject> m_dataStack;
public:
    Interpreter() : m_currentScope(), m_dataStack() {}

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

private:
    bool isNumeric(DurianObject o) const {
        return o.type == DurianType::Integer || o.type == DurianType::Double;
    }
};

