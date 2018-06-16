#include <gtest/gtest.h>

#include <Lexer.h>

void checkToken(Token tok, TokenType expectedType, uint32_t expectedLine, std::string expectedLit) {
    EXPECT_EQ(tok.type, expectedType);
    EXPECT_EQ(tok.line, expectedLine);
    EXPECT_EQ(tok.literal, expectedLit);
}

TEST(TestLexer, TestSingleComma) {
    Lexer lexer(",");
    checkToken(lexer.getToken(), TokenType::Comma, 1, "");
}

TEST(TestLexer, TestParenCommaParen) {
    Lexer lexer("(,)");
    checkToken(lexer.getToken(), TokenType::LeftParen, 1, "");
    checkToken(lexer.getToken(), TokenType::Comma, 1, "");
    checkToken(lexer.getToken(), TokenType::RightParen, 1, "");
}

TEST(TestLexer, TestString) {
    Lexer lexer("\"Hi, this is a string.\"");
    checkToken(lexer.getToken(), TokenType::String, 1, "Hi, this is a string.");
}

TEST(TestLexer, TestIgnoreWhitespace) {
    Lexer lexer("  ( ,) }");
    checkToken(lexer.getToken(), TokenType::LeftParen, 1, "");
    checkToken(lexer.getToken(), TokenType::Comma, 1, "");
    checkToken(lexer.getToken(), TokenType::RightParen, 1, "");
    checkToken(lexer.getToken(), TokenType::RightBrace, 1, "");
}

TEST(TestLexer, TestFunctionDef) {
    Lexer lexer("def add(a,b) {\r\nreturn a + b\r\n}");
    checkToken(lexer.getToken(), TokenType::Def, 1, "");
    checkToken(lexer.getToken(), TokenType::Identifier, 1, "add");
    checkToken(lexer.getToken(), TokenType::LeftParen, 1, "");
    checkToken(lexer.getToken(), TokenType::Identifier, 1, "a");
    checkToken(lexer.getToken(), TokenType::Comma, 1, "");
    checkToken(lexer.getToken(), TokenType::Identifier, 1, "b");
    checkToken(lexer.getToken(), TokenType::RightParen, 1, "");
    checkToken(lexer.getToken(), TokenType::LeftBrace, 1, "");
    checkToken(lexer.getToken(), TokenType::EOL, 1, "");
    checkToken(lexer.getToken(), TokenType::Return, 2, "");
    checkToken(lexer.getToken(), TokenType::Identifier, 2, "a");
    checkToken(lexer.getToken(), TokenType::Plus, 2, "");
    checkToken(lexer.getToken(), TokenType::Identifier, 2, "b");
    checkToken(lexer.getToken(), TokenType::EOL, 2, "");
    checkToken(lexer.getToken(), TokenType::RightBrace, 3, "");
}

TEST(TestLexer, TestEatDurianEx) {
    Lexer lexer("def EatDurianHelper(durian, callback) {\n"
                "    print durian & \" is eaten!\"\n"
                "    let success = callback(durian)\n"
                "    return success\n"
                "}");
    checkToken(lexer.getToken(), TokenType::Def, 1, "");
    checkToken(lexer.getToken(), TokenType::Identifier, 1, "EatDurianHelper");
    checkToken(lexer.getToken(), TokenType::LeftParen, 1, "");
    checkToken(lexer.getToken(), TokenType::Identifier, 1, "durian");
    checkToken(lexer.getToken(), TokenType::Comma, 1, "");
    checkToken(lexer.getToken(), TokenType::Identifier, 1, "callback");
    checkToken(lexer.getToken(), TokenType::RightParen, 1, "");
    checkToken(lexer.getToken(), TokenType::LeftBrace, 1, "");
    checkToken(lexer.getToken(), TokenType::EOL, 1, "");
    checkToken(lexer.getToken(), TokenType::Print, 2, "");
    checkToken(lexer.getToken(), TokenType::Identifier, 2, "durian");
    checkToken(lexer.getToken(), TokenType::Ampersand, 2, "");
    checkToken(lexer.getToken(), TokenType::String, 2, " is eaten!");
    checkToken(lexer.getToken(), TokenType::EOL, 2, "");
    checkToken(lexer.getToken(), TokenType::Let, 3, "");
    checkToken(lexer.getToken(), TokenType::Identifier, 3, "success");
    checkToken(lexer.getToken(), TokenType::Equal, 3, "");
    checkToken(lexer.getToken(), TokenType::Identifier, 3, "callback");
    checkToken(lexer.getToken(), TokenType::LeftParen, 3, "");
    checkToken(lexer.getToken(), TokenType::Identifier, 3, "durian");
    checkToken(lexer.getToken(), TokenType::RightParen, 3, "");
    checkToken(lexer.getToken(), TokenType::EOL, 3, "");
    checkToken(lexer.getToken(), TokenType::Return, 4, "");
    checkToken(lexer.getToken(), TokenType::Identifier, 4, "success");
    checkToken(lexer.getToken(), TokenType::EOL, 4, "");
    checkToken(lexer.getToken(), TokenType::RightBrace, 5, "");
}

