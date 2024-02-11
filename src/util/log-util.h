#ifndef LOG_UTIL_H
#define LOG_UTIL_H

#include <iostream>
#include <ostream>

class Logger {
    std::ostream &stream;

public:
    explicit Logger(std::ostream &os, const std::string &prefix): stream(os) {
        os << prefix;
    }

    template<class T>
    Logger &operator <<(const T &v) {
        stream << v;
        return *this;
    }

    ~Logger() {
        stream << std::endl;
    }
};

#define STD_LOG Logger(std::cout, "alp: ")
#define ERR_LOG Logger(std::cerr, "alp: ")
#define TEST_LOG Logger(std::cout, "[INFO] ")
#define TEST_ERR_LOG Logger(std::cerr, "[ERROR] ")

#endif //LOG_UTIL_H
