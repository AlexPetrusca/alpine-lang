#include "util/test-util.h"
#include "../src/lexer/lexer.h"

const std::string SOURCE_EXT = ".alp";
const std::string LEXER_EXT = ".lex";
const std::string PARSE_EXT = ".ast";

void expect_output_eq(Lexer lexer, std::ifstream& lex_file) {
    while (lexer.has_next()) {
        Token token = lexer.get_token();
        std::string expected;
        getline(lex_file, expected);
        if (expected == "NEW_LINE") {
            expected = "\n";
        }
        EXPECT_EQ(expected, token.value);
    }
}

void test_lexer_output(const std::string& test_file_path) {
    std::ifstream source_file = open_file(test_file_path + SOURCE_EXT);
    std::ifstream lex_file = open_file(test_file_path + LEXER_EXT);
    Lexer lexer(source_file);
    expect_output_eq(lexer, lex_file);
}

TEST(TokenizerTest, OneToken) {
    test_lexer_output("examples/one-token");
}

TEST(TokenizerTest, OneLine) {
    test_lexer_output("examples/one-line");
}

TEST(TokenizerTest, MultiLine) {
    test_lexer_output("examples/multi-line");
}

TEST(TokenizerTest, MultiLinePadded) {
    test_lexer_output("examples/multi-line-padded");
}

TEST(TokenizerTest, MultiLineMisformat) {
    test_lexer_output("examples/multi-line-misformat");
}
