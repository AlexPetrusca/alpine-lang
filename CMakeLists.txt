cmake_minimum_required(VERSION 3.28)
project(alpine_lang)

set(CMAKE_CXX_STANDARD 23)

find_package(fmt CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

set(LIBS fmt::fmt)
set(TEST_LIBS ${LIBS} GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

set(FILES
        src/util/log-util.h
        src/util/set-util.h
        src/lexer/lexer.cpp
        src/lexer/lexer.h
        src/lexer/token.cpp
        src/lexer/token.h
        src/parser/parser.cpp
        src/parser/parser.h
        src/parser/syntax_tree.cpp
        src/parser/syntax_tree.h
)

set(TEST_FILES
        test/util/test-util.h
        test/lexer_test.cpp
        test/parser_test.cpp
        test/syntax_tree_test.cpp
)

# main executable

add_executable(alp main.cpp
        ${FILES}
)

target_link_libraries(alp PRIVATE ${LIBS})

# test executable

enable_testing()

add_executable(alp-test ${FILES} ${TEST_FILES})

target_link_libraries(alp-test PRIVATE ${TEST_LIBS})

add_test(TokenizerTests alp-test)