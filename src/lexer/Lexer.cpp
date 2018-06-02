#include <Lexer.h>

Lexer::Lexer(const std::string input)
    : m_input(input)
    , m_iter(input.cbegin())
    , m_line(1)
{

}

Token Lexer::getToken() {
    std::string literal;
    if (m_iter == m_input.cend()) return Token {TokenType::END, m_line, ""};
    while (*m_iter == ' ') {
        ++m_iter;
    }
    switch (*m_iter) {
        case ',':
            ++m_iter;
            return Token {TokenType::Comma, m_line, ""};
        case '{':
            ++m_iter;
            return Token {TokenType::LeftBrace, m_line, ""};
        case '}':
            ++m_iter;
            return Token {TokenType::RightBrace, m_line, ""};
        case '(':
            ++m_iter;
            return Token {TokenType::LeftParen, m_line, ""};
        case ')':
            ++m_iter;
            return Token {TokenType::RightParen, m_line, ""};
        case '&':
            ++m_iter;
            return Token {TokenType::Ampersand, m_line, ""};
        case '+':
            ++m_iter;
            return Token {TokenType::Plus, m_line, ""};
        case '-':
            ++m_iter;
            return Token {TokenType::Minus, m_line, ""};
        case '*':
            ++m_iter;
            return Token {TokenType::Star, m_line, ""};
        case '/':
            ++m_iter;
            return Token {TokenType::Slash, m_line, ""};
        case '=':
            ++m_iter;
            if (*m_iter == '=') {
                ++m_iter;
                return Token {TokenType::EqualEqual, m_line, ""};
            }
            return Token {TokenType::Equal, m_line, ""};
        case '!':
            ++m_iter;
            if (*m_iter == '=') {
                ++m_iter;
                return Token {TokenType::BangEqual, m_line, ""};
            }
            return Token {TokenType::Bang, m_line, ""};
        case '>':
            ++m_iter;
            if (*m_iter == '=') {
                ++m_iter;
                return Token {TokenType::GreaterEqual, m_line, ""};
            }
            return Token {TokenType::Greater, m_line, ""};
        case '<':
            ++m_iter;
            if (*m_iter == '=') {
                ++m_iter;
                return Token {TokenType::LesserEqual, m_line, ""};
            }
            return Token {TokenType::Lesser, m_line, ""};
        case '\n':
            ++m_iter;
            return Token {TokenType::EOL, m_line++, ""};
        case '\r':
            ++m_iter;
            if (*m_iter == '\n') {
                ++m_iter;
                return Token {TokenType::EOL, m_line++, ""};
            }
            return Token {TokenType::Error, m_line, "Found carriage return but no newline."};
        case '"':
            while (*(++m_iter) != '"') {
                literal += *m_iter;
            }
            ++m_iter;
            return Token {TokenType::String, m_line, literal};
        default:
            // TODO check if token is digit or alphabetic
            // if digit: parse as int or float
            // if alphabetic: parse until whitespace (?),
            // then check against list of keywords
            return Token {TokenType::Error, m_line, "No matching token for character."};
    }
}