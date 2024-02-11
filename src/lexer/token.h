#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token {
public:
    enum Type {
        Identifier,
        DecimalLiteral,
        LeftParentheses,
        RightParentheses,
        Equals,
        Plus,
        Minus,
        Multiply,
        Divide,
        NewLine,
        Eof,
        Unk
    };

    std::string value;
    Type type;
    size_t line;
    size_t pos;

    explicit Token();

    explicit Token(std::string value);

    explicit Token(std::string value, size_t line, size_t pos);

    [[nodiscard]] std::string to_string() const;

    friend std::ostream &operator <<(std::ostream &os, const Token &t);
};

#endif //TOKEN_H
