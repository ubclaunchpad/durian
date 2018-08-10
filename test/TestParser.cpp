#include <gtest/gtest.h>

#include <Parser.h>
#include <cstdio>

TEST(TestParser, TestIfStatementNoElse) {
    Parser parser(Lexer("if a {\n    break\n}"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* ifStmt = dynamic_cast<AST::IfStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> condExpr = std::move(ifStmt->m_condition);
    auto* ident = dynamic_cast<AST::Identifier*>(condExpr.get());
    ASSERT_EQ(ident->m_identStr, "a");
    std::unique_ptr<AST::BlockStmt> trueBody = std::move(ifStmt->m_trueBody);
    std::unique_ptr<AST::Stmt> firstStmt = std::move(trueBody->m_statements.front());
    auto* breakStmt = dynamic_cast<AST::BreakStmt*>(firstStmt.get());
    ASSERT_EQ(nullptr, ifStmt->m_falseBody);
}

TEST(TestParser, TestMultilevelIfStatement) {
    Parser parser(Lexer("if a {\n    break\n} elif b {\n    next\n} else {\n    break\n}"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* ifStmt = dynamic_cast<AST::IfStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> condExpr = std::move(ifStmt->m_condition);
    auto* ident = dynamic_cast<AST::Identifier*>(condExpr.get());
    ASSERT_EQ(ident->m_identStr, "a");
    std::unique_ptr<AST::BlockStmt> trueBody = std::move(ifStmt->m_trueBody);
    std::unique_ptr<AST::Stmt> firstStmt = std::move(trueBody->m_statements.front());
    auto* breakStmt = dynamic_cast<AST::BreakStmt*>(firstStmt.get());
    std::unique_ptr<AST::Stmt> falseBody = std::move(ifStmt->m_falseBody);
    auto* elifStmt = dynamic_cast<AST::IfStmt*>(falseBody.get());
    condExpr = std::move(elifStmt->m_condition);
    ident = dynamic_cast<AST::Identifier*>(condExpr.get());
    ASSERT_EQ(ident->m_identStr, "b");
    trueBody = std::move(elifStmt->m_trueBody);
    firstStmt = std::move(trueBody->m_statements.front());
    auto* nextStmt = dynamic_cast<AST::NextStmt*>(firstStmt.get());
    falseBody = std::move(elifStmt->m_falseBody);
    auto* blockStmt = dynamic_cast<AST::BlockStmt*>(falseBody.get());
    firstStmt = std::move(blockStmt->m_statements.front());
    breakStmt = dynamic_cast<AST::BreakStmt*>(firstStmt.get());
    ASSERT_EQ(nullptr, ifStmt->m_falseBody);
}

TEST(TestParser, TestWhileStatement) {
    Parser parser(Lexer("while a {\n    break\n}"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* whileStmt = dynamic_cast<AST::WhileStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> condExpr = std::move(whileStmt->m_condition);
    auto* ident = dynamic_cast<AST::Identifier*>(condExpr.get());
    ASSERT_EQ(ident->m_identStr, "a");
    std::unique_ptr<AST::BlockStmt> body = std::move(whileStmt->m_body);
    std::unique_ptr<AST::Stmt> firstStmt = std::move(body->m_statements.front());
    auto* breakStmt = dynamic_cast<AST::BreakStmt*>(firstStmt.get());
}

TEST(TestParser, TestReturnStatement) {
    Parser parser(Lexer("return a"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* retStmt = dynamic_cast<AST::ReturnStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> retVal = std::move(retStmt->m_expr);
    auto* ident = dynamic_cast<AST::Identifier*>(retVal.get());
    ASSERT_EQ(ident->m_identStr, "a");
}

TEST(TestParser, TestLetStatement) {
    Parser parser(Lexer("let a = 1"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* letStmt = dynamic_cast<AST::LetStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> lval = std::move(letStmt->m_ident);
    auto* ident = dynamic_cast<AST::Identifier*>(lval.get());
    ASSERT_EQ(ident->m_identStr, "a");
    std::unique_ptr<AST::Expr> val = std::move(letStmt->m_expr);
    auto* lit = dynamic_cast<AST::IntegerLit*>(val.get());
    ASSERT_EQ(lit->m_value, 1);
}

TEST(TestParser, TestAssignStatement) {
    Parser parser(Lexer("a = 1"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* assignStmt = dynamic_cast<AST::AssignStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> lval = std::move(assignStmt->m_ident);
    auto* ident = dynamic_cast<AST::Identifier*>(lval.get());
    ASSERT_EQ(ident->m_identStr, "a");
    std::unique_ptr<AST::Expr> val = std::move(assignStmt->m_expr);
    auto* lit = dynamic_cast<AST::IntegerLit*>(val.get());
    ASSERT_EQ(lit->m_value, 1);
}

TEST(TestParser, TestPrintStatement) {
    Parser parser(Lexer("print a"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* printStmt = dynamic_cast<AST::PrintStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> expr = std::move(printStmt->m_expr);
    auto* ident = dynamic_cast<AST::Identifier*>(expr.get());
    ASSERT_EQ(ident->m_identStr, "a");
}

TEST(TestParser, TestErrStatement) {
    Parser parser(Lexer("err a"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* errStmt = dynamic_cast<AST::ErrStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> expr = std::move(errStmt->m_expr);
    auto* ident = dynamic_cast<AST::Identifier*>(expr.get());
    ASSERT_EQ(ident->m_identStr, "a");
}

TEST(TestParser, TestScanStatement) {
    Parser parser(Lexer("scan a"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* scanStmt = dynamic_cast<AST::ScanStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> expr = std::move(scanStmt->m_ident);
    auto* ident = dynamic_cast<AST::Identifier*>(expr.get());
    ASSERT_EQ(ident->m_identStr, "a");
}

// TODO fix function declaration parsing! (works in debugger but not otherwise...)
//TEST(TestParser, TestFnDecl) {
//    Parser parser(Lexer(
//            R"delim(def f(a,b) {
//                        return 1.0
//                    })delim"));
//    std::unique_ptr<AST::Stmt> stmt = parser.parse();
//    auto* fnDecl = dynamic_cast<AST::FnDecl*>(stmt.get());
//    std::unique_ptr<AST::Expr> expr = std::move(fnDecl->m_ident);
//    auto* ident = dynamic_cast<AST::Identifier*>(expr.get());
//    ASSERT_EQ(ident->m_identStr, "f");
//    std::vector<std::unique_ptr<AST::Identifier>> params = std::move(fnDecl->m_params);
//    ASSERT_EQ(params[0]->m_identStr, "a");
//    ASSERT_EQ(params[1]->m_identStr, "b");
//    std::unique_ptr<AST::BlockStmt> body = std::move(fnDecl->m_body);
//    std::unique_ptr<AST::Stmt> firstStmt = std::move(body->m_statements.front());
//    auto* breakStmt = dynamic_cast<AST::BreakStmt*>(firstStmt.get());
//}

TEST(TestParser, TestUnaryPlusExpr) {
    Parser parser(Lexer("+a"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* exprStmt = dynamic_cast<AST::ExprStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> expr = std::move(exprStmt->m_expr);
    auto* plusExpr = dynamic_cast<AST::UnaryExpr*>(expr.get());
    ASSERT_EQ(plusExpr->m_op, TokenType::Plus);
    std::unique_ptr<AST::Expr> operand = std::move(plusExpr->m_operand);
    auto* ident = dynamic_cast<AST::Identifier*>(operand.get());
    ASSERT_EQ(ident->m_identStr, "a");
}

TEST(TestParser, TestUnaryMinusExpr) {
    Parser parser(Lexer("-a"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* exprStmt = dynamic_cast<AST::ExprStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> expr = std::move(exprStmt->m_expr);
    auto* minusExpr = dynamic_cast<AST::UnaryExpr*>(expr.get());
    ASSERT_EQ(minusExpr->m_op, TokenType::Minus);
    std::unique_ptr<AST::Expr> operand = std::move(minusExpr->m_operand);
    auto* ident = dynamic_cast<AST::Identifier*>(operand.get());
    ASSERT_EQ(ident->m_identStr, "a");
}

TEST(TestParser, TestNegateExpr) {
    Parser parser(Lexer("!a"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* exprStmt = dynamic_cast<AST::ExprStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> expr = std::move(exprStmt->m_expr);
    auto* negateExpr = dynamic_cast<AST::UnaryExpr*>(expr.get());
    ASSERT_EQ(negateExpr->m_op, TokenType::Bang);
    std::unique_ptr<AST::Expr> operand = std::move(negateExpr->m_operand);
    auto* ident = dynamic_cast<AST::Identifier*>(operand.get());
    ASSERT_EQ(ident->m_identStr, "a");
}

TEST(TestParser, TestUnaryStringifyExpr) {
    Parser parser(Lexer("&a"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* exprStmt = dynamic_cast<AST::ExprStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> expr = std::move(exprStmt->m_expr);
    auto* stringifyExpr = dynamic_cast<AST::UnaryExpr*>(expr.get());
    ASSERT_EQ(stringifyExpr->m_op, TokenType::Ampersand);
    std::unique_ptr<AST::Expr> operand = std::move(stringifyExpr->m_operand);
    auto* ident = dynamic_cast<AST::Identifier*>(operand.get());
    ASSERT_EQ(ident->m_identStr, "a");
}

TEST(TestParser, TestAndExpr) {
    Parser parser(Lexer("a and b"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* exprStmt = dynamic_cast<AST::ExprStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> expr = std::move(exprStmt->m_expr);
    auto* andExpr = dynamic_cast<AST::BinaryExpr*>(expr.get());
    ASSERT_EQ(andExpr->m_op, TokenType::And);
    std::unique_ptr<AST::Expr> left = std::move(andExpr->m_left);
    auto* lident = dynamic_cast<AST::Identifier*>(left.get());
    std::unique_ptr<AST::Expr> right = std::move(andExpr->m_right);
    auto* rident = dynamic_cast<AST::Identifier*>(right.get());
    ASSERT_EQ(lident->m_identStr, "a");
    ASSERT_EQ(rident->m_identStr, "b");
}

TEST(TestParser, TestOrExpr) {
    Parser parser(Lexer("a or b"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* exprStmt = dynamic_cast<AST::ExprStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> expr = std::move(exprStmt->m_expr);
    auto* orExpr = dynamic_cast<AST::BinaryExpr*>(expr.get());
    ASSERT_EQ(orExpr->m_op, TokenType::Or);
    std::unique_ptr<AST::Expr> left = std::move(orExpr->m_left);
    auto* lident = dynamic_cast<AST::Identifier*>(left.get());
    std::unique_ptr<AST::Expr> right = std::move(orExpr->m_right);
    auto* rident = dynamic_cast<AST::Identifier*>(right.get());
    ASSERT_EQ(lident->m_identStr, "a");
    ASSERT_EQ(rident->m_identStr, "b");
}

TEST(TestParser, TestAddExpr) {
    Parser parser(Lexer("a + b"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* exprStmt = dynamic_cast<AST::ExprStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> expr = std::move(exprStmt->m_expr);
    auto* addExpr = dynamic_cast<AST::BinaryExpr*>(expr.get());
    ASSERT_EQ(addExpr->m_op, TokenType::Plus);
    std::unique_ptr<AST::Expr> left = std::move(addExpr->m_left);
    auto* lident = dynamic_cast<AST::Identifier*>(left.get());
    std::unique_ptr<AST::Expr> right = std::move(addExpr->m_right);
    auto* rident = dynamic_cast<AST::Identifier*>(right.get());
    ASSERT_EQ(lident->m_identStr, "a");
    ASSERT_EQ(rident->m_identStr, "b");
}

TEST(TestParser, TestSubExpr) {
    Parser parser(Lexer("a - b"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* exprStmt = dynamic_cast<AST::ExprStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> expr = std::move(exprStmt->m_expr);
    auto* subExpr = dynamic_cast<AST::BinaryExpr*>(expr.get());
    ASSERT_EQ(subExpr->m_op, TokenType::Minus);
    std::unique_ptr<AST::Expr> left = std::move(subExpr->m_left);
    auto* lident = dynamic_cast<AST::Identifier*>(left.get());
    std::unique_ptr<AST::Expr> right = std::move(subExpr->m_right);
    auto* rident = dynamic_cast<AST::Identifier*>(right.get());
    ASSERT_EQ(lident->m_identStr, "a");
    ASSERT_EQ(rident->m_identStr, "b");
}

TEST(TestParser, TestMulExpr) {
    Parser parser(Lexer("a * b"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* exprStmt = dynamic_cast<AST::ExprStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> expr = std::move(exprStmt->m_expr);
    auto* mulExpr = dynamic_cast<AST::BinaryExpr*>(expr.get());
    ASSERT_EQ(mulExpr->m_op, TokenType::Star);
    std::unique_ptr<AST::Expr> left = std::move(mulExpr->m_left);
    auto* lident = dynamic_cast<AST::Identifier*>(left.get());
    std::unique_ptr<AST::Expr> right = std::move(mulExpr->m_right);
    auto* rident = dynamic_cast<AST::Identifier*>(right.get());
    ASSERT_EQ(lident->m_identStr, "a");
    ASSERT_EQ(rident->m_identStr, "b");
}

TEST(TestParser, TestDivExpr) {
    Parser parser(Lexer("a / b"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* exprStmt = dynamic_cast<AST::ExprStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> expr = std::move(exprStmt->m_expr);
    auto* divExpr = dynamic_cast<AST::BinaryExpr*>(expr.get());
    ASSERT_EQ(divExpr->m_op, TokenType::Slash);
    std::unique_ptr<AST::Expr> left = std::move(divExpr->m_left);
    auto* lident = dynamic_cast<AST::Identifier*>(left.get());
    std::unique_ptr<AST::Expr> right = std::move(divExpr->m_right);
    auto* rident = dynamic_cast<AST::Identifier*>(right.get());
    ASSERT_EQ(lident->m_identStr, "a");
    ASSERT_EQ(rident->m_identStr, "b");
}

TEST(TestParser, TestEqualExpr) {
    Parser parser(Lexer("a == b"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* exprStmt = dynamic_cast<AST::ExprStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> expr = std::move(exprStmt->m_expr);
    auto* equalExpr = dynamic_cast<AST::BinaryExpr*>(expr.get());
    ASSERT_EQ(equalExpr->m_op, TokenType::EqualEqual);
    std::unique_ptr<AST::Expr> left = std::move(equalExpr->m_left);
    auto* lident = dynamic_cast<AST::Identifier*>(left.get());
    std::unique_ptr<AST::Expr> right = std::move(equalExpr->m_right);
    auto* rident = dynamic_cast<AST::Identifier*>(right.get());
    ASSERT_EQ(lident->m_identStr, "a");
    ASSERT_EQ(rident->m_identStr, "b");
}

TEST(TestParser, TestNotEqualExpr) {
    Parser parser(Lexer("a != b"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* exprStmt = dynamic_cast<AST::ExprStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> expr = std::move(exprStmt->m_expr);
    auto* equalExpr = dynamic_cast<AST::BinaryExpr*>(expr.get());
    ASSERT_EQ(equalExpr->m_op, TokenType::BangEqual);
    std::unique_ptr<AST::Expr> left = std::move(equalExpr->m_left);
    auto* lident = dynamic_cast<AST::Identifier*>(left.get());
    std::unique_ptr<AST::Expr> right = std::move(equalExpr->m_right);
    auto* rident = dynamic_cast<AST::Identifier*>(right.get());
    ASSERT_EQ(lident->m_identStr, "a");
    ASSERT_EQ(rident->m_identStr, "b");
}

TEST(TestParser, TestGreaterExpr) {
    Parser parser(Lexer("a > b"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* exprStmt = dynamic_cast<AST::ExprStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> expr = std::move(exprStmt->m_expr);
    auto* gtExpr = dynamic_cast<AST::BinaryExpr*>(expr.get());
    ASSERT_EQ(gtExpr->m_op, TokenType::Greater);
    std::unique_ptr<AST::Expr> left = std::move(gtExpr->m_left);
    auto* lident = dynamic_cast<AST::Identifier*>(left.get());
    std::unique_ptr<AST::Expr> right = std::move(gtExpr->m_right);
    auto* rident = dynamic_cast<AST::Identifier*>(right.get());
    ASSERT_EQ(lident->m_identStr, "a");
    ASSERT_EQ(rident->m_identStr, "b");
}

TEST(TestParser, TestGreaterEqualExpr) {
    Parser parser(Lexer("a >= b"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* exprStmt = dynamic_cast<AST::ExprStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> expr = std::move(exprStmt->m_expr);
    auto* geExpr = dynamic_cast<AST::BinaryExpr*>(expr.get());
    ASSERT_EQ(geExpr->m_op, TokenType::GreaterEqual);
    std::unique_ptr<AST::Expr> left = std::move(geExpr->m_left);
    auto* lident = dynamic_cast<AST::Identifier*>(left.get());
    std::unique_ptr<AST::Expr> right = std::move(geExpr->m_right);
    auto* rident = dynamic_cast<AST::Identifier*>(right.get());
    ASSERT_EQ(lident->m_identStr, "a");
    ASSERT_EQ(rident->m_identStr, "b");
}

TEST(TestParser, TestLesserExpr) {
    Parser parser(Lexer("a < b"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* exprStmt = dynamic_cast<AST::ExprStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> expr = std::move(exprStmt->m_expr);
    auto* ltExpr = dynamic_cast<AST::BinaryExpr*>(expr.get());
    ASSERT_EQ(ltExpr->m_op, TokenType::Lesser);
    std::unique_ptr<AST::Expr> left = std::move(ltExpr->m_left);
    auto* lident = dynamic_cast<AST::Identifier*>(left.get());
    std::unique_ptr<AST::Expr> right = std::move(ltExpr->m_right);
    auto* rident = dynamic_cast<AST::Identifier*>(right.get());
    ASSERT_EQ(lident->m_identStr, "a");
    ASSERT_EQ(rident->m_identStr, "b");
}

TEST(TestParser, TestLesserEqualExpr) {
    Parser parser(Lexer("a <= b"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* exprStmt = dynamic_cast<AST::ExprStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> expr = std::move(exprStmt->m_expr);
    auto* leExpr = dynamic_cast<AST::BinaryExpr*>(expr.get());
    ASSERT_EQ(leExpr->m_op, TokenType::LesserEqual);
    std::unique_ptr<AST::Expr> left = std::move(leExpr->m_left);
    auto* lident = dynamic_cast<AST::Identifier*>(left.get());
    std::unique_ptr<AST::Expr> right = std::move(leExpr->m_right);
    auto* rident = dynamic_cast<AST::Identifier*>(right.get());
    ASSERT_EQ(lident->m_identStr, "a");
    ASSERT_EQ(rident->m_identStr, "b");
}

TEST(TestParser, TestIdentifier) {
    Parser parser(Lexer("a"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* exprStmt = dynamic_cast<AST::ExprStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> subExpr = std::move(exprStmt->m_expr);
    auto* ident = dynamic_cast<AST::Identifier*>(subExpr.get());
    ASSERT_EQ(ident->m_identStr, "a");
}

TEST(TestParser, TestStringConcatAssoc) {
    Parser parser(Lexer("a & b & c"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* exprStmt = dynamic_cast<AST::ExprStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> expr = std::move(exprStmt->m_expr);
    auto* stringConcatExpr = dynamic_cast<AST::BinaryExpr*>(expr.get());
    ASSERT_EQ(stringConcatExpr->m_op, TokenType::Ampersand);
    std::unique_ptr<AST::Expr> left = std::move(stringConcatExpr->m_left);
    auto* subStringConcatExpr = dynamic_cast<AST::BinaryExpr*>(left.get());
    ASSERT_EQ(subStringConcatExpr->m_op, TokenType::Ampersand);
    std::unique_ptr<AST::Expr> subSubLeft = std::move(subStringConcatExpr->m_left);
    std::unique_ptr<AST::Expr> subSubRight = std::move(subStringConcatExpr->m_right);
    auto* sublident = dynamic_cast<AST::Identifier*>(subSubLeft.get());
    auto* subrident = dynamic_cast<AST::Identifier*>(subSubRight.get());
    ASSERT_EQ(sublident->m_identStr, "a");
    ASSERT_EQ(subrident->m_identStr, "b");
    std::unique_ptr<AST::Expr> right = std::move(stringConcatExpr->m_right);
    auto* rident = dynamic_cast<AST::Identifier*>(right.get());
    ASSERT_EQ(rident->m_identStr, "c");
}

TEST(TestParser, TestMultiPrecedenceExpr) {
    Parser parser(Lexer("a * b + c * d"));
    std::unique_ptr<AST::Stmt> stmt = parser.parse();
    auto* exprStmt = dynamic_cast<AST::ExprStmt*>(stmt.get());
    std::unique_ptr<AST::Expr> expr = std::move(exprStmt->m_expr);
    auto* mulExpr = dynamic_cast<AST::BinaryExpr*>(expr.get());
    ASSERT_EQ(mulExpr->m_op, TokenType::Plus);
    std::unique_ptr<AST::Expr> left = std::move(mulExpr->m_left);
    std::unique_ptr<AST::Expr> right = std::move(mulExpr->m_right);
    auto* leftAddExpr = dynamic_cast<AST::BinaryExpr*>(left.get());
    auto* rightAddExpr = dynamic_cast<AST::BinaryExpr*>(right.get());
    ASSERT_EQ(leftAddExpr->m_op, TokenType::Star);
    ASSERT_EQ(rightAddExpr->m_op, TokenType::Star);
    std::unique_ptr<AST::Expr> leftleft = std::move(leftAddExpr->m_left);
    std::unique_ptr<AST::Expr> leftright = std::move(leftAddExpr->m_right);
    std::unique_ptr<AST::Expr> rightleft = std::move(rightAddExpr->m_left);
    std::unique_ptr<AST::Expr> rightright = std::move(rightAddExpr->m_right);
    auto* llident = dynamic_cast<AST::Identifier*>(leftleft.get());
    auto* lrident = dynamic_cast<AST::Identifier*>(leftright.get());
    auto* rlident = dynamic_cast<AST::Identifier*>(rightleft.get());
    auto* rrident = dynamic_cast<AST::Identifier*>(rightright.get());
    ASSERT_EQ(llident->m_identStr, "a");
    ASSERT_EQ(lrident->m_identStr, "b");
    ASSERT_EQ(rlident->m_identStr, "c");
    ASSERT_EQ(rrident->m_identStr, "d");
}

