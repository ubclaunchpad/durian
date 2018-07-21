#pragma once

#include <cstdint>
#include <string>
#include <iostream>
#include <opcode.h>

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

inline std::string tokTypeToString(const TokenType type) {
    switch (type) {
        case TokenType::Comma: return ",";
        case TokenType::LeftBrace: return "{";
        case TokenType::RightBrace: return "}";
        case TokenType::LeftParen: return "(";
        case TokenType::RightParen: return ")";
        case TokenType::And: return "and";
        case TokenType::Or: return "or";
        case TokenType::Ampersand: return "&";
        case TokenType::Plus: return "+";
        case TokenType::Minus: return "-";
        case TokenType::Star: return "*";
        case TokenType::Slash: return "/";
        case TokenType::BangEqual: return "!=";
        case TokenType::EqualEqual: return "==";
        case TokenType::Greater: return ">";
        case TokenType::GreaterEqual: return ">=";
        case TokenType::Lesser: return "<";
        case TokenType::LesserEqual: return "<=";
        case TokenType::True: return "True";
        case TokenType::False: return "False";
        case TokenType::Def: return "def";
        case TokenType::Let: return "let";
        case TokenType::Equal: return "=";
        case TokenType::Bang: return "!";
        case TokenType::If: return "if";
        case TokenType::Else: return "else";
        case TokenType::Elif: return "elif";
        case TokenType::While: return "while";
        case TokenType::Return: return "return";
        case TokenType::Next: return "next";
        case TokenType::Break: return "break";
        case TokenType::Print: return "print";
        case TokenType::Scan: return "scan";
        case TokenType::Err: return "err";
        case TokenType::EOL: return "EOL";
        case TokenType::END: return "EOF";
        case TokenType::String:
        case TokenType::Integer:
        case TokenType::Float: return "Literal";
        case TokenType::Identifier: return "Identifier";
        case TokenType::Error: return "Lexing error";
    }
}

inline constexpr unsigned char getBinOpcode(TokenType type) {
    switch (type) {
        case TokenType::Ampersand:
            return Opcode::CNCT;
        case TokenType::Plus:
            return Opcode::ADD;
        case TokenType::Minus:
            return Opcode::SUB;
        case TokenType::Star:
            return Opcode::MUL;
        case TokenType::Slash:
            return Opcode::FDIV;
        case TokenType::EqualEqual:
            return Opcode::EQ;
            // TODO other cases
        default:
            // this should never happen
            std::cout << "Token " << tokTypeToString(type) << " has no binary opcode translation." << std::endl;
            exit(1);
    }
}

inline constexpr unsigned char getUnOpcode(TokenType type) {
    switch (type) {
        case TokenType::Plus:
            return Opcode::POS;
        case TokenType::Minus:
            return Opcode::NEG;
        case TokenType::Bang:
            return Opcode::NOT;
        case TokenType::Ampersand:
            return Opcode::STRFY;
        default:
            // this should never happen
            std::cout << "Token " << tokTypeToString(type) << " has no unary opcode translation." << std::endl;
            exit(1);
    }
}

struct Token {
    TokenType type;
    uint32_t line;
    std::string literal;
    std::string toString() {
        if (type == TokenType::String ||
            type == TokenType::Integer ||
            type == TokenType::Float ||
            type == TokenType::Identifier ||
            type == TokenType::Error) {
            return literal;
        } else return tokTypeToString(type);
    }
};


