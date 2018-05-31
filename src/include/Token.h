#pragma once

#include <cstdint>
#include <string>

enum struct TokenType {
    // Delimiters
    Comma, LeftBrace, RightBrace, LeftParen, RightParen,

    // General operators
    And, Or, Ampersand, Plus, Minus, Star, Slash,

    // Comparison operators
    BangEqual, EqualEqual, Greater, GreaterEqual, Lesser, LesserEqual,

    // Literals
    String, Integer, Float, True, False,

    // State-related tokens
    Def, Let, Equal, Identifier,

    // Control-flow keywords
    Bang, And, Or, If, Else, Elif, While, Return, Next, Break,

    // I/O keywords
    Print, Scan, Err,

    // File tokens
    EOL, EOF
};

struct Token {
    TokenType type;
    uint32_t line;
    std::string literal;
};