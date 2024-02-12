#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <fstream>

#include "token.h"

class Lexer {
    std::ifstream &file;

    size_t line;
    size_t pos;
    char ch;
    char next_ch;

    Token token;
    Token next_token;

public:
    explicit Lexer(std::ifstream &f);

    Token peek_token();

    Token get_token();

    [[nodiscard]] bool has_next() const;

    ~Lexer();

private:
    void advance_token();

    void consume_char(char c);

    void advance_char_to_next_valid();

    void advance_char_to_newline();

    void advance_char_ignore_whitespace();

    void advance_char();

    [[nodiscard]] bool is_eof() const;

    [[nodiscard]] bool is_line_comment() const;

    [[nodiscard]] bool is_valid_sequence() const;

    [[nodiscard]] bool is_whitespace_sequence() const;

    [[nodiscard]] bool is_empty_line() const;
};

#endif //TOKENIZER_H
