#include <stdexcept>

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
    EXPECT_THROW(
        try { parser.parse(); } catch (const std::runtime_error& e) {
            EXPECT_STREQ(e.what(), "Expected a number, received: +");
            throw;
        },
        std::runtime_error);
}

/**
 * Subtraction
 */

/**
 * Multiplication
 */

TEST(ExpressionParserMultiplication, NoWhitespace) {
    ExpressionParser parser("2*2");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 4);
}

TEST(ExpressionParserMultiplication, OperatorLeadingWhitespace) {
    ExpressionParser parser("2 *2");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 4);
}

TEST(ExpressionParserMultiplication, OperatorTrailingWhitespace) {
    ExpressionParser parser("2* 2");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 4);
}

TEST(ExpressionParserMultiplication, OperatorLeadingAndTrailingWhitespace) {
    ExpressionParser parser("2 * 2");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 4);
}

TEST(ExpressionParserMultiplication, LeadingWhitespace) {
    ExpressionParser parser(" 2*2");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 4);
}

TEST(ExpressionParserMultiplication, TrailingWhitespace) {
    ExpressionParser parser("2*2 ");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 4);
}

TEST(ExpressionParserMultiplication, OperatorLeadingAndTrailingWhitespaceAndExpressionLeadingAndTrailingWhitespace) {
    ExpressionParser parser(" 2 * 2 ");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 4);
}

TEST(ExpressionParserMultiplication, NegativeMultiplyNegative) {
    ExpressionParser parser("-2*-2");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 4);
}

TEST(ExpressionParserMultiplication, NegativeMultiplyPositive) {
    ExpressionParser parser("-2*4");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), -8);
}

TEST(ExpressionParserMultiplication, PositiveMultiplyNegative) {
    ExpressionParser parser("3*-2");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), -6);
}

// Failures
TEST(ExprsesionParserMultiplication, DuplicateMultiplyOperator) {
    ExpressionParser parser("2**2");
    EXPECT_THROW(
        try { parser.parse(); } catch (const std::runtime_error& e) {
            EXPECT_STREQ(e.what(), "Expected a number, received: *");
            throw;
        },
        std::runtime_error);
}

/**
 * Exponentiation
 */

/**
 * Modulus
 */

/**
 * Full Expressions
 */