#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <fstream>

#include "token.h"

class Tokenizer {
    std::ifstream &file;

    size_t line;
    size_t pos;
    char ch;

    std::string token;
    std::string next_token;

public:
    explicit Tokenizer(std::ifstream &f);

    Token peek_token();

    Token get_token();

    bool has_next();

    ~Tokenizer();

private:
    void advance_token();

    void advance_char_to_newline();

    void advance_char();

    char peek_char();

    void advance_char_ignore_whitespace();

    bool is_whitespace_sequence();

    void advance_char_to_next_valid();

    bool is_eof();

    bool is_line_comment();

    bool is_valid_sequence();

    bool is_empty_line();
};

#endif //TOKENIZER_H
