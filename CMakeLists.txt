cmake_minimum_required(VERSION 3.28)
project(alpine_lang)

set(CMAKE_CXX_STANDARD 23)

find_package(fmt CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

set(LIBS fmt::fmt)
set(TEST_LIBS ${LIBS} GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

# main executable

add_executable(alp main.cpp
        src/util/log-util.h
        src/util/set-util.h
        src/lexer/tokenizer.cpp
        src/lexer/tokenizer.h
        src/lexer/Token.cpp
        src/lexer/Token.h
)

target_link_libraries(alp PRIVATE ${LIBS})

# test executable

#enable_testing()

add_executable(alp-test test/test.cpp
        src/util/log-util.h
        src/util/set-util.h
        src/lexer/tokenizer.cpp
        src/lexer/tokenizer.h
        src/lexer/Token.cpp
        src/lexer/Token.h
        test/util/test-util.h
)

target_link_libraries(alp-test PRIVATE ${TEST_LIBS})

add_test(TokenizerTests alp-test)