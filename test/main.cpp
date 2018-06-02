#include <gtest/gtest.h>

#include <ExampleClass.h>
#include <Lexer.h>

TEST(TestExClass, TestRetOne) {
    EXPECT_EQ(ExampleClass::returnOne(), 1);
}

TEST(TestLexer, TestSingleComma) {
    Lexer lexer(",");
    Token tok = lexer.getToken();
    EXPECT_EQ(tok.type, TokenType::Comma);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.literal, "");
}

TEST(TestLexer, TestParenCommaParen) {
    Lexer lexer("(,)");
    Token tok1 = lexer.getToken();
    Token tok2 = lexer.getToken();
    Token tok3 = lexer.getToken();
    EXPECT_EQ(tok1.type, TokenType::LeftParen);
    EXPECT_EQ(tok1.line, 1);
    EXPECT_EQ(tok1.literal, "");
    EXPECT_EQ(tok2.type, TokenType::Comma);
    EXPECT_EQ(tok2.line, 1);
    EXPECT_EQ(tok2.literal, "");
    EXPECT_EQ(tok3.type, TokenType::RightParen);
    EXPECT_EQ(tok3.line, 1);
    EXPECT_EQ(tok3.literal, "");
}

TEST(TestLexer, TestString) {
    Lexer lexer("\"Hi, this is a string.\"");
    Token tok = lexer.getToken();
    EXPECT_EQ(tok.type, TokenType::String);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.literal, "Hi, this is a string.");
}

TEST(TestLexer, TestIgnoreWhitespace) {
    Lexer lexer("  ( ,) }");
    Token tok1 = lexer.getToken();
    Token tok2 = lexer.getToken();
    Token tok3 = lexer.getToken();
    Token tok4 = lexer.getToken();
    EXPECT_EQ(tok1.type, TokenType::LeftParen);
    EXPECT_EQ(tok1.line, 1);
    EXPECT_EQ(tok1.literal, "");
    EXPECT_EQ(tok2.type, TokenType::Comma);
    EXPECT_EQ(tok2.line, 1);
    EXPECT_EQ(tok2.literal, "");
    EXPECT_EQ(tok3.type, TokenType::RightParen);
    EXPECT_EQ(tok3.line, 1);
    EXPECT_EQ(tok3.literal, "");
    EXPECT_EQ(tok4.type, TokenType::RightBrace);
    EXPECT_EQ(tok4.line, 1);
    EXPECT_EQ(tok4.literal, "");
}