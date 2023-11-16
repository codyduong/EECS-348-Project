#include "gtest/gtest.h"
#include "../src/ExpressionParser.h"

TEST(ExpressionParserAddition, BasicAddition) {
    ExpressionParser parser("1+1");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 2);
}

TEST(ExpressionParserAddition, BasicAdditionWithWhitespace1) {
    ExpressionParser parser("1 +1");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 2);
}

TEST(ExpressionParserAddition, BasicAdditionWithWhitespace2) {
    ExpressionParser parser("1+ 1");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 2);
}

TEST(ExpressionParserAddition, BasicAdditionWithWhitespace3) {
    ExpressionParser parser("1 + 1");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 2);
}
