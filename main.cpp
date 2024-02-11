#include <iostream>
#include <fstream>
#include <getopt.h>

#include "src/lexer/lexer.h"
#include "src/util/log-util.h"

void execute() {

}

void parse() {

}

void print_file(std::ifstream & file) {
    std::string line;
    while (getline(file, line)) {
        std::cout << line << std::endl;
    }
    std::cout << "\n-------------------------\n" << std::endl;
    file.clear();
    file.seekg(0);
}

void compile(std::ifstream & file) {
    print_file(file);

    Lexer lexer(file);

    while (lexer.has_next()) {
        STD_LOG << lexer.get_token();
    }

    // tokenize
    // parse
    // execute
}

void print_usage(const int code) {
    std::cout << "usage: alp -[h] file" << std::endl;
    exit(code);
}

int main(const int argc, char** argv) {
    constexpr option longopts[] = {
        {"help", optional_argument, nullptr, 'h'}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, ":h", longopts, nullptr)) != -1) {
        switch (opt) {
            case 'h':
                print_usage(EXIT_SUCCESS);
        }
    }

    if (optind >= argc) {
        print_usage(EXIT_FAILURE);
    }

    std::ifstream file(argv[optind]);
    if (!file.is_open()) {
        ERR_LOG << "could not open file: " << argv[optind];
        exit(EXIT_FAILURE);
    }

    compile(file);

    exit(EXIT_SUCCESS);
}
