#include "lexer.h"
#include "../util/set-util.h"

const std::set WHITESPACE_CHARS = {' ', '\t'};
const std::set SPECIAL_CHARS = {'(', ')', '=', '+', '-', '*', '/', '\n'};
const std::set<char> STOP_CHARS = merge_sets(WHITESPACE_CHARS, SPECIAL_CHARS);

Lexer::Lexer(std::ifstream &f): file(f) {
    line = 0;
    pos = 0;
    ch = '\0';
    token = Token();
    next_token = Token("\n"); // effectively, add a newline at start of file
    advance_char();
    advance_token();
}

Token Lexer::peek_token() {
    return token;
}

Token Lexer::get_token() {
    advance_token();
    return token;
}

bool Lexer::has_next() const {
    return !next_token.value.empty();
}

void Lexer::advance_token() {
    token = next_token;
    next_token = Token();

    advance_char_to_next_valid();

    if (SPECIAL_CHARS.contains(ch)) { // handle operators & special symbols
        consume_char(ch);
    } else { // handle keywords & identifiers & literals
        while (!STOP_CHARS.contains(ch) && ch != EOF) {
            consume_char(ch);
        }
    }

    // effectively, add a newline at end of file, if there isnt one
    if (token.value != "\n" && is_eof()) {
        consume_char('\n');
    }
}

void Lexer::consume_char(const char ch) {
    // update value
    next_token.value += ch;
    advance_char();

    // resolve type
    if (next_token.value.length() == 1) {
        if (ch == '(') {
            next_token.type = Token::LeftParentheses;
        } else if (ch == ')') {
            next_token.type = Token::RightParentheses;
        } else if (ch == '=') {
            next_token.type = Token::Equals;
        } else if (ch == '+') {
            next_token.type = Token::Plus;
        } else if (ch == '-') {
            next_token.type = Token::Minus;
        } else if (ch == '*') {
            next_token.type = Token::Multiply;
        } else if (ch == '/') {
            next_token.type = Token::Divide;
        } else if (ch == '\n') {
            next_token.type = Token::NewLine;
        } else if (isdigit(ch)) {
            next_token.type = Token::DecimalLiteral;
        } else if (isalpha(ch) || ch == '_') {
            next_token.type = Token::Identifier;
        }
    } else if (isdigit(ch)) {
        if (next_token.type != Token::DecimalLiteral && next_token.type != Token::Identifier) {
            next_token.type = Token::Unk;
        }
    } else if (isalnum(ch) || ch == '_') {
        if (next_token.type != Token::Identifier) {
            next_token.type = Token::Unk;
        }
    }
}

void Lexer::advance_char_to_next_valid() {
    while (is_valid_sequence()) {
        advance_char_ignore_whitespace();
        if (is_line_comment()) {
            advance_char_to_newline();
        }
    }
    next_token.pos = pos;
    next_token.line = line;
}

void Lexer::advance_char_to_newline() {
    while (ch != '\n' && ch != EOF) {
        advance_char();
    }
}

void Lexer::advance_char_ignore_whitespace() {
    while (is_whitespace_sequence()) {
        advance_char();
    }
}

bool Lexer::is_valid_sequence() const {
    return is_whitespace_sequence() || is_line_comment();
}

bool Lexer::is_whitespace_sequence() const {
    return WHITESPACE_CHARS.contains(ch) || is_empty_line();
}

bool Lexer::is_empty_line() const {
    return ch == '\n' && token.value == "\n";
}

bool Lexer::is_line_comment() const {
    return ch == '/' && peek_char() == '/';
}

void Lexer::advance_char() {
    pos++;
    if (ch == '\n') {
        pos = 0;
        line++;
    }
    ch = static_cast<char>(file.get());
}

char Lexer::peek_char() const {
    const char c = static_cast<char>(file.get());
    file.unget();
    return c;
}

bool Lexer::is_eof() const {
    return !token.value.empty() && next_token.value.empty();
}

Lexer::~Lexer() {
    file.close();
}
