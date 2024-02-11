#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token {
public:
    enum Type {
        Identifier,
        Literal,
        NewLine,
        Plus,
        Minus,
        Multiply,
        Divide,
        Equals,
        Eof
    };

    std::string value;
    Type type;
    size_t line;
    size_t pos;

    explicit Token(std::string value, size_t line, size_t pos);

    [[nodiscard]] std::string to_string() const;

    friend std::ostream &operator <<(std::ostream &os, const Token &t) {
        return os << t.to_string();
    }
};

#endif //TOKEN_H
