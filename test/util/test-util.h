#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <fstream>
#include <gtest/gtest.h>

inline std::ifstream open_file(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        ADD_FAILURE() << "Could not open file: " << path;
        exit(EXIT_FAILURE);
    }
    return file;
}

#endif //TEST_UTIL_H
