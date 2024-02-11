#include <fmt/core.h>
#include <unordered_map>

#include "token.h"

std::unordered_map<Token::Type, std::string> type2name = {
    {Token::Identifier, "IDENTIFIER"},
    {Token::Literal, "LITERAL"},
    {Token::NewLine, "NEW_LINE"},
    {Token::Plus, "+"},
    {Token::Minus, "-"},
    {Token::Multiply, "*"},
    {Token::Divide, "/"},
    {Token::Equals, "="},
    {Token::Eof, "EOF"}
};

Token::Token(std::string value, const size_t line, const size_t pos): value(std::move(value)), line(line), pos(pos) {
    type = Identifier;
}

std::string Token::to_string() const {
    return fmt::format("{} ({}, line: {}, pos: {})", value, type2name[type], line, pos);
}
