#include <gtest/gtest.h>

#include <Parser.h>

TEST(TestParser, TestParseFunctionDefAndCall) {
    Parser parser(Lexer(R"example(
def add(a, b) {
    return a + b
}
add(5, 6)
)example"));
    parser.parse();
}
