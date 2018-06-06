#include <gtest/gtest.h>

#include <Lexer.h>

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

TEST(TestLexer, TestFunctionDef) {
    Lexer lexer("def add(a,b) {\r\nreturn a + b\r\n}");
    Token tok = lexer.getToken();
    EXPECT_EQ(tok.type, TokenType::Def);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.literal, "");
    tok = lexer.getToken();
    EXPECT_EQ(tok.type, TokenType::Identifier);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.literal, "add");
    tok = lexer.getToken();
    EXPECT_EQ(tok.type, TokenType::LeftParen);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.literal, "");
    tok = lexer.getToken();
    EXPECT_EQ(tok.type, TokenType::Identifier);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.literal, "a");
    tok = lexer.getToken();
    EXPECT_EQ(tok.type, TokenType::Comma);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.literal, "");
    tok = lexer.getToken();
    EXPECT_EQ(tok.type, TokenType::Identifier);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.literal, "b");
    tok = lexer.getToken();
    EXPECT_EQ(tok.type, TokenType::RightParen);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.literal, "");
    tok = lexer.getToken();
    EXPECT_EQ(tok.type, TokenType::LeftBrace);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.literal, "");
    tok = lexer.getToken();
    EXPECT_EQ(tok.type, TokenType::EOL);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.literal, "");
    tok = lexer.getToken();
    EXPECT_EQ(tok.type, TokenType::Return);
    EXPECT_EQ(tok.line, 2);
    EXPECT_EQ(tok.literal, "");
    tok = lexer.getToken();
    EXPECT_EQ(tok.type, TokenType::Identifier);
    EXPECT_EQ(tok.line, 2);
    EXPECT_EQ(tok.literal, "a");
    tok = lexer.getToken();
    EXPECT_EQ(tok.type, TokenType::Plus);
    EXPECT_EQ(tok.line, 2);
    EXPECT_EQ(tok.literal, "");
    tok = lexer.getToken();
    EXPECT_EQ(tok.type, TokenType::Identifier);
    EXPECT_EQ(tok.line, 2);
    EXPECT_EQ(tok.literal, "b");
    tok = lexer.getToken();
    EXPECT_EQ(tok.type, TokenType::EOL);
    EXPECT_EQ(tok.line, 2);
    EXPECT_EQ(tok.literal, "");
    tok = lexer.getToken();
    EXPECT_EQ(tok.type, TokenType::RightBrace);
    EXPECT_EQ(tok.line, 3);
    EXPECT_EQ(tok.literal, "");
}
