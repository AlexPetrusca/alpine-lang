#include "util/test-util.h"
#include "../src/parser/syntax_tree.h"

TEST(SyntaxTreeTest, BasicConstruction) {
    SyntaxTree tree = SyntaxTree();
    tree.add_child(SyntaxTree(Token("1"), SyntaxTree::Integer));
    tree.add_child(SyntaxTree(Token("+"), SyntaxTree::BinaryOperator));
    tree.add_child(SyntaxTree(Token("1"), SyntaxTree::Integer));

    char* tree_str = strdup(tree.to_string().c_str());
    const std::string line0 = strtok(tree_str, "\n");
    EXPECT_TRUE(line0.contains("ROOT"));
    const std::string line1 = strtok(nullptr, "\n");
    EXPECT_TRUE(line1.contains("INTEGER"));
    const std::string line2 = strtok(nullptr, "\n");
    EXPECT_TRUE(line2.contains("BINARY_OPERATOR"));
    const std::string line3 = strtok(nullptr, "\n");
    EXPECT_TRUE(line3.contains("INTEGER"));
    char *line4 = strtok(nullptr, "\n");
    EXPECT_EQ(line4, nullptr);
    delete tree_str;
}
