#include "tokenizer.h"

#include "../util/set-util.h"

const std::set WHITESPACE_CHARS = {' ', '\t'};
const std::set SPECIAL_CHARS = {'(', ')', '=', '+', '-', '*', '/', '\n'};
const std::set<char> STOP_CHARS = merge_sets(WHITESPACE_CHARS, SPECIAL_CHARS);

Tokenizer::Tokenizer(std::ifstream &f): file(f) {
    line = 0;
    pos = 0;
    ch = '\0';
    token = "";
    next_token = "\n"; // effectively, add a newline at start of file
    advance_char();
    advance_token();
}

Token Tokenizer::peek_token() {
    return Token(token, line, pos - token.length() - 1);
}

Token Tokenizer::get_token() {
    advance_token();
    return Token(token, line, pos - token.length() - 1);
}

bool Tokenizer::has_next() {
    return !next_token.empty();
}

void Tokenizer::advance_token() {
    token = next_token;
    next_token = "";

    advance_char_to_next_valid();

    if (SPECIAL_CHARS.contains(ch)) { // handle operators & special symbols
        next_token += ch;
        advance_char();
    } else { // handle keywords & identifiers & literals
        while (!STOP_CHARS.contains(ch) && ch != EOF) {
            next_token += ch;
            advance_char();
        }
    }

    // effectively, add a newline at end of file, if there isnt one
    if (token != "\n" && is_eof()) {
        next_token = "\n";
    }
}

void Tokenizer::advance_char_to_next_valid() {
    while (is_valid_sequence()) {
        advance_char_ignore_whitespace();
        if (is_line_comment()) {
            advance_char_to_newline();
        }
    }
}

void Tokenizer::advance_char_to_newline() {
    while (ch != '\n' && ch != EOF) {
        advance_char();
    }
}

void Tokenizer::advance_char_ignore_whitespace() {
    while (is_whitespace_sequence()) {
        advance_char();
    }
}

bool Tokenizer::is_valid_sequence() {
    return is_whitespace_sequence() || is_line_comment();
}

bool Tokenizer::is_whitespace_sequence() {
    return WHITESPACE_CHARS.contains(ch) || is_empty_line();
}

bool Tokenizer::is_empty_line() {
    return ch == '\n' && token == "\n";
}

bool Tokenizer::is_line_comment() {
    return ch == '/' && peek_char() == '/';
}

void Tokenizer::advance_char() {
    pos++;
    ch = static_cast<char>(file.get());
}

char Tokenizer::peek_char() {
    const char c = static_cast<char>(file.get());
    file.unget();
    return c;
}

bool Tokenizer::is_eof() {
    return !token.empty() && next_token.empty();
}

Tokenizer::~Tokenizer() {
    file.close();
}
