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
    Bang, If, Else, Elif, While, Return, Next, Break,

    // I/O keywords
    Print, Scan, Err,

    // Control tokens
    // Note: END represents EOF;
    // however EOF is defined as a macro in the standard library
    // and so is unusable here
    EOL, END, Error
};

struct Token {
    TokenType type;
    uint32_t line;
    std::string literal;
};