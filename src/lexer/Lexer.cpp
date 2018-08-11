#include <Lexer.h>

Lexer::Lexer(const std::string& input)
    : m_input(input)
    , m_iter(input.cbegin())
    , m_line(1)
{

}

const Token Lexer::getToken() {
    std::string literal;
    if (m_iter == m_input.cend() || *m_iter =='\0') return Token {TokenType::END, m_line, ""};
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
            // NOTE: apparently \r alone was used in older systems but we uh won't support those
            return Token {TokenType::Error, m_line, "Found carriage return but no newline."};
        case '"':
            while (*(++m_iter) != '"') {
                literal += *m_iter;
            }
            ++m_iter;
            return Token {TokenType::String, m_line, literal};
        default:
            const char c = *m_iter;
            literal += c;
            if (isDigit(c)) {
                // numeric literal
                while (isDigit(*(++m_iter))) {
                    literal += *m_iter;
                }
                if (*m_iter == '.') {
                    literal += *m_iter;
                    while (isDigit(*(++m_iter))) {
                        literal += *m_iter;
                    }
                    return Token {TokenType::Float, m_line, literal};
                } else {
                    return Token {TokenType::Integer, m_line, literal};
                }
            }
            else if (isAlpha(c)) {
                // identifier or reserved keyword
                while (isIdentChar(*(++m_iter))) {
                    literal += *m_iter;
                }
                if (literal == "and") return Token {TokenType::And, m_line, ""};
                if (literal == "or") return  Token {TokenType::Or, m_line, ""};
                if (literal == "True") return Token {TokenType::True, m_line, ""};
                if (literal == "False") return Token {TokenType::False, m_line, ""};
                if (literal == "def") return Token {TokenType::Def, m_line, ""};
                if (literal == "let") return Token {TokenType::Let, m_line, ""};
                if (literal == "if") return Token {TokenType::If, m_line, ""};
                if (literal == "else") return Token {TokenType::Else, m_line, ""};
                if (literal == "elif") return Token {TokenType::Elif, m_line, ""};
                if (literal == "while") return Token {TokenType::While, m_line, ""};
                if (literal == "return") return Token {TokenType::Return, m_line, ""};
                if (literal == "next") return Token {TokenType::Next, m_line, ""};
                if (literal == "break") return Token {TokenType::Break, m_line, ""};
                if (literal == "print") return Token {TokenType::Print, m_line, ""};
                if (literal == "scan") return Token {TokenType::Scan, m_line, ""};
                if (literal == "err") return Token {TokenType::Err, m_line, ""};
                return Token {TokenType::Identifier, m_line, literal};
            }
            std::string errChar;
            errChar.push_back(c);
            return Token {TokenType::Error, m_line, errChar};
    }
}

bool Lexer::isDigit(const char c) const {
    return (isdigit(c) != 0);
}

bool Lexer::isAlpha(const char c) const {
    return (isalpha(c) != 0);
}

bool Lexer::isIdentChar(const char c) const {
    return isDigit(c) || isAlpha(c) || c == '_';
}
