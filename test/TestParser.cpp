#include <gtest/gtest.h>

#include <Parser.h>

TEST(TestLexer, TestFunctionDefAndCall) {
    Parser parser(R"example(
def add(a, b) {
    return a + b
}
add(5, 6)
)example");
    auto tree = parser.buildTree();
}
