#include <fmt/core.h>
#include <unordered_map>

#include "syntax_tree.h"

static std::unordered_map<SyntaxTree::Type, std::string> type_name = {
    {SyntaxTree::Root, "ROOT"},
    {SyntaxTree::BinaryOperator, "BINARY_OPERATOR"},
    {SyntaxTree::UnaryOperator, "UNARY_OPERATOR"},
    {SyntaxTree::Integer, "INTEGER"},
    {SyntaxTree::Identifier, "IDENTIFIER"},
    {SyntaxTree::Expression, "EXPRESSION"},
    {SyntaxTree::Statement, "STATEMENT"},
    {SyntaxTree::FunctionCall, "FUNCTION_CALL"},
    {SyntaxTree::Arguements, "ARGUMENTS"},
};

SyntaxTree::SyntaxTree() {
    type = Root;
    children = std::vector<SyntaxTree>();
}

SyntaxTree::SyntaxTree(Token token, const Type type): token(std::move(token)), type(type) {
    children = std::vector<SyntaxTree>();
}


void SyntaxTree::add_child(const SyntaxTree &node) {
    children.push_back(node);
}

std::string SyntaxTree::to_string() const {
    return to_string(0);
}

std::string SyntaxTree::to_string(const int level) const {
    const std::string spacing(level, '\t');
    std::string str = fmt::format("{}{}({})\n", spacing, type_name[type], token.value);
    for (const SyntaxTree &child: children) {
        str += child.to_string(level + 1);
    }
    return str;
}

std::ostream & operator<<(std::ostream &os, const SyntaxTree &st) {
    return os << st.to_string();
}
