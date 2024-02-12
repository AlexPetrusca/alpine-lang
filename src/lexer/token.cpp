#include <fmt/core.h>
#include <unordered_map>

#include "token.h"

static std::unordered_map<Token::Type, std::string> type_name = {
    {Token::Identifier, "IDENTIFIER"},
    {Token::DecimalLiteral, "DECIMAL_LITERAL"},
    {Token::LeftParentheses, "LEFT_PARENTHESES"},
    {Token::RightParentheses, "RIGHT_PARENTHESES"},
    {Token::Equals, "EQUALS"},
    {Token::Plus, "PLUS"},
    {Token::Minus, "MINUS"},
    {Token::Multiply, "MULTIPLY"},
    {Token::Divide, "DIVIDE"},
    {Token::NewLine, "NEW_LINE"},
    {Token::Eof, "EOF"},
    {Token::Unk, "UNK"}
};

Token::Token() {
    value = "";
    line = 0;
    pos = 0;
    type = Eof;
}

Token::Token(std::string value): value(std::move(value)) {
    line = 0;
    pos = 0;
    type = Eof;
}

Token::Token(std::string value, const size_t line, const size_t pos): value(std::move(value)), line(line), pos(pos) {
    type = Eof;
}

std::string Token::to_string() const {
    std::string display = (value != "\n") ? value : "\\n";
    const std::string spacing((5 - display.length() / 4), '\t');
    return fmt::format("{}{}({}, line: {}, pos: {})", display, spacing, type_name[type], line, pos);
}

std::ostream & operator<<(std::ostream &os, const Token &t) {
    return os << t.to_string();
}
