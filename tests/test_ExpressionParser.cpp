#include "../src/ExpressionParser.h"
#include "gtest/gtest.h"

/**
 * Special Cases
 */
TEST(ExpressionParserSpecial, UnaryNegative) {
    ExpressionParser parser("-1");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), -1);
}

/**
 * Addition
 */
TEST(ExpressionParserAddition, NoWhitespace) {
    ExpressionParser parser("1+1");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 2);
}

TEST(ExpressionParserAddition, OperatorLeadingWhitespace) {
    ExpressionParser parser("1 +1");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 2);
}

TEST(ExpressionParserAddition, OperatorTrailingWhitespace) {
    ExpressionParser parser("1+ 1");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 2);
}

TEST(ExpressionParserAddition, OperatorLeadingAndTrailingWhitespace) {
    ExpressionParser parser("1 + 1");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 2);
}

TEST(ExpressionParserAddition, LeadingWhitespace) {
    ExpressionParser parser(" 1+1");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 2);
}

TEST(ExpressionParserAddition, TrailingWhitespace) {
    ExpressionParser parser("1+1 ");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 2);
}

TEST(ExpressionParserAddition, OperatorLeadingAndTrailingWhitespaceAndExpressionLeadingAndTrailingWhitespace) {
    ExpressionParser parser(" 1 + 1 ");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 2);
}

TEST(ExpressionParserAddition, NegativeAddNegative) {
    ExpressionParser parser("-1+-1");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), -2);
}

TEST(ExpressionParserAddition, NegativeAddPositive) {
    ExpressionParser parser("-1+5");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 4);
}

TEST(ExpressionParserAddition, PositiveAddNegative) {
    ExpressionParser parser("1+-4");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), -3);
}

// Failures
TEST(ExprsesionParserAdditon, DuplicateAddOperator) {
    ExpressionParser parser("1++1");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_THROW(ast->evaluate(), std::runtime_error);
}

/**
 * Subtraction
 */

/**
 * Multiplication
 */

/**
 * Exponentiation
 */

/**
 * Modulus
 */

/**
 * Full Expressions
 */