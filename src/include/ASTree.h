#pragma once

#include <Token.h>
#include <Visitor.h>

#include <ios>
#include <memory>
#include <sstream>
#include <vector>

namespace AST {

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

struct Stmt {
    virtual ~Stmt() = default;
    virtual void accept(Visitor *visitor) = 0;
};

struct BlockStmt : public Stmt {
    std::vector<std::unique_ptr<Stmt>> m_statements;
    explicit BlockStmt(std::vector<std::unique_ptr<Stmt>> statements)
        : m_statements(std::move(statements)) { }
    virtual void accept(Visitor *visitor) { visitor->visit(this); }
};

struct IfStmt : public Stmt {
    std::unique_ptr<Expr> m_condition;
    std::unique_ptr<BlockStmt> m_trueBody;
    // note: if an `else` statement this will be a BlockStmt
    // if an `elif` statement this will be another IfStmt
    // otherwise nullptr
    std::unique_ptr<Stmt> m_falseBody;
    explicit IfStmt(std::unique_ptr<Expr> condition,
                    std::unique_ptr<BlockStmt> trueBody,
                    std::unique_ptr<Stmt> falseBody)
        : m_condition(std::move(condition))
        , m_trueBody(std::move(trueBody))
        , m_falseBody(std::move(falseBody)) { }
    virtual void accept(Visitor *visitor) { visitor->visit(this); }
};

struct WhileStmt : public Stmt {
    std::unique_ptr<Expr> m_condition;
    std::unique_ptr<BlockStmt> m_body;
    explicit WhileStmt(std::unique_ptr<Expr> condition, std::unique_ptr<BlockStmt> body)
        : m_condition(std::move(condition))
        , m_body(std::move(body)) { }
    virtual void accept(Visitor *visitor) { visitor->visit(this); }
};

struct NextStmt : public Stmt {
    virtual void accept(Visitor *visitor) { visitor->visit(this); }
};

struct BreakStmt : public Stmt {
    virtual void accept(Visitor *visitor) { visitor->visit(this); }
};

struct LetStmt : public Stmt {
    std::unique_ptr<Identifier> m_ident;
    std::unique_ptr<Expr> m_expr;
    explicit LetStmt(std::unique_ptr<Identifier> ident, std::unique_ptr<Expr> expr)
        : m_ident(std::move(ident))
        , m_expr(std::move(expr)) { }
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};

struct AssignStmt : public Stmt {
    std::unique_ptr<Expr> m_ident;
    std::unique_ptr<Expr> m_expr;
    explicit AssignStmt(std::unique_ptr<Expr> ident, std::unique_ptr<Expr> expr)
        : m_ident(std::move(ident))
        , m_expr(std::move(expr)) { }
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};

struct PrintStmt : public Stmt {
    std::unique_ptr<Expr> m_expr;
    explicit PrintStmt(std::unique_ptr<Expr> expr)
        : m_expr(std::move(expr)) { }
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};

struct ErrStmt : public Stmt {
    std::unique_ptr<Expr> m_expr;
    explicit ErrStmt(std::unique_ptr<Expr> expr)
       : m_expr(std::move(expr)) { }
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};

struct ScanStmt : public Stmt {
    std::unique_ptr<Identifier> m_ident;
    explicit ScanStmt(std::unique_ptr<Identifier> ident)
        : m_ident(std::move(ident)) { }
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};

struct FnDecl : public Stmt {
    std::unique_ptr<Identifier> m_ident;
    std::vector<std::unique_ptr<Identifier>> m_params;
    std::unique_ptr<BlockStmt> m_body;
    explicit FnDecl(std::unique_ptr<Identifier> ident,
                    std::vector<std::unique_ptr<Identifier>> params,
                    std::unique_ptr<BlockStmt> body)
        : m_ident(std::move(ident))
        , m_params(std::move(params))
        , m_body(std::move(body)) { }
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};

struct ReturnStmt : public Stmt {
    std::unique_ptr<Expr> m_expr;
    explicit ReturnStmt(std::unique_ptr<Expr> expr)
        : m_expr(std::move(expr)) { }
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};

//////////////////////////////////////////
/// Expressions

struct Expr : public Stmt { };

struct BinaryExpr : public Expr {
    TokenType m_op;
    std::unique_ptr<Expr> m_left;
    std::unique_ptr<Expr> m_right;
    explicit BinaryExpr(TokenType op, std::unique_ptr<Expr> left, std::unique_ptr<Expr> right)
        : m_op(op)
        , m_left(std::move(left))
        , m_right(std::move(right)) { }
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};

struct UnaryExpr : public Expr {
    TokenType m_op;
    std::unique_ptr<Expr> m_operand;
    explicit UnaryExpr(TokenType op, std::unique_ptr<Expr> operand)
        : m_op(op)
        , m_operand(std::move(operand)) { }
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};

struct IntegerLit: public Expr {
    int64_t m_value;
    explicit IntegerLit(const std::string &value) : m_value(std::stoll(value)) { }
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};

struct FloatLit: public Expr {
    double m_value;
    explicit FloatLit(const std::string &value) : m_value(std::stod(value)) { }
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};

struct StringLit: public Expr {
    const std::string m_value;
    explicit StringLit(const std::string &value) : m_value(value) { }
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};

struct BooleanLit: public Expr {
    bool m_value;
    explicit BooleanLit(bool val) : m_value(val) { }
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};

struct Identifier : public Expr {
    const std::string m_identStr;
    explicit Identifier(const std::string identStr) : m_identStr(identStr) { }
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};

struct FnCall : public Expr {
    std::unique_ptr<Identifier> m_ident;
    std::vector<std::unique_ptr<Expr>> m_args;
    explicit FnCall(std::unique_ptr<Identifier> ident, std::vector<std::unique_ptr<Expr>> args)
        : m_ident(std::move(ident))
        , m_args(std::move(args)) { }
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};

struct ExprStmt : public Stmt {
    std::unique_ptr<Expr> m_expr;
    explicit ExprStmt(std::unique_ptr<Expr> expr) : m_expr(std::move(expr)) {}
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};

}
