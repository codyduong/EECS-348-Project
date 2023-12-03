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

/*
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
            EXPECT_STREQ(e.what(), "Expected a expression or number, received: +");
            throw;
        },
        std::runtime_error);
}

/**
 * Subtraction
 */
TEST(ExpressionParserSubtraction, NoWhitespace) {
    ExpressionParser parser("1-1");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 0);
}

TEST(ExpressionParserSubtraction, OperatorLeadingWhitespace) {
    ExpressionParser parser("1 -1");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 0);
}

TEST(ExpressionParserSubtraction, OperatorTrailingWhitespace) {
    ExpressionParser parser("1- 1");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 0);
}

TEST(ExpressionParserSubtraction, OperatorLeadingAndTrailingWhitespace) {
    ExpressionParser parser("1 - 1");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 0);
}

TEST(ExpressionParserSubtraction, LeadingWhitespace) {
    ExpressionParser parser(" 1-1");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 0);
}

TEST(ExpressionParserSubtraction, TrailingWhitespace) {
    ExpressionParser parser("1-1 ");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 0);
}

TEST(ExpressionParserSubtraction, OperatorLeadingAndTrailingWhitespaceAndExpressionLeadingAndTrailingWhitespace) {
    ExpressionParser parser(" 1 - 1 ");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 0);
}

TEST(ExpressionParserSubtraction, NegativeSubtractNegative) {
    ExpressionParser parser("-1--1");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 0);
}

TEST(ExpressionParserSubtraction, NegativeSubtractPositive) {
    ExpressionParser parser("-1-5");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), -6);
}

TEST(ExpressionParserSubtraction, PositiveSubtractNegative) {
    ExpressionParser parser("1--4");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 5);
}

// Failures
TEST(ExprsesionParserMultiplication, DuplicateSubtractOperator) {
    // We have do to it this way, because our unary operator - means it can be stacked infinitly, ie 1--1, and 1---1 are parsed to 1+1 and 1-1 respectively.
    ExpressionParser parser("2-(-)");
    EXPECT_THROW(
        try { parser.parse(); } catch (const std::runtime_error& e) {
            // Also recieve a ) instead of a -, because - will be parsed as a unary modifier
            EXPECT_STREQ(e.what(), "Expected a expression or number, received: )");
            throw;
        },
        std::runtime_error);
}

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
            EXPECT_STREQ(e.what(), "Expected a expression or number, received: *");
            throw;
        },
        std::runtime_error);
}

/**
 * Exponentiation
 */
TEST(ExpressionParserExponentiation, PositiveExponentPositive) {
    ExpressionParser parser("2^3");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 8);
}

TEST(ExpressionParserExponentiation, NegativeBasePositiveExponent) {
    ExpressionParser parser("-2^2");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 4);
}

TEST(ExpressionParserExponentiation, PositiveBaseNegativeExponent) {
    ExpressionParser parser("3^(-2)");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_DOUBLE_EQ(ast->evaluate(), 1.0 / 9.0);
}

TEST(ExpressionParserExponentiation, BaseWithWhitespaceExponent) {
    ExpressionParser parser("2 ^ 4");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 16);
}

TEST(ExpressionParserExponentiation, ExponentiationWithMultipleOperators) {
    ExpressionParser parser("2 + 3^2");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 11);
}

TEST(ExpressionParserExponentiation, ExponentiationWithParentheses) {
    ExpressionParser parser("(2 + 3)^2");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 25);
}

TEST(ExpressionParserExponentiation, ExponentiationWithNegativeBaseAndExponent) {
    ExpressionParser parser("(-2)^(-3)");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_DOUBLE_EQ(ast->evaluate(), -0.125);
}

TEST(ExpressionParserExponentiation, ExponentiationWithNegativeBase) {
    ExpressionParser parser("(-2)^3");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), -8);
}

TEST(ExpressionParserExponentiation, ExponentiationWithZeroBase) {
    ExpressionParser parser("0^2");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 0);
}

TEST(ExpressionParserExponentiation, ExponentiationWithZeroExponent) {
    ExpressionParser parser("3^0");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 1);
}

// Failures
TEST(ExprsesionParserMultiplication, DuplicateExponentOperator) {
    ExpressionParser parser("2^^2");
    EXPECT_THROW(
        try { parser.parse(); } catch (const std::runtime_error& e) {
            EXPECT_STREQ(e.what(), "Expected a expression or number, received: ^");
            throw;
        },
        std::runtime_error);
}

/**
 * Modulus
 */
TEST(ExpressionParserModulus, NoWhitespace) {
    ExpressionParser parser("7%3");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 1);
}

TEST(ExpressionParserModulus, OperatorLeadingWhitespace) {
    ExpressionParser parser("7 %3");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 1);
}

TEST(ExpressionParserModulus, OperatorTrailingWhitespace) {
    ExpressionParser parser("7% 3");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 1);
}

TEST(ExpressionParserModulus, OperatorLeadingAndTrailingWhitespace) {
    ExpressionParser parser("7 % 3");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 1);
}

TEST(ExpressionParserModulus, LeadingWhitespace) {
    ExpressionParser parser(" 7%3");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 1);
}

TEST(ExpressionParserModulus, TrailingWhitespace) {
    ExpressionParser parser("7%3 ");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 1);
}

TEST(ExpressionParserModulus, OperatorLeadingAndTrailingWhitespaceAndExpressionLeadingAndTrailingWhitespace) {
    ExpressionParser parser(" 7 % 3 ");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 1);
}

TEST(ExpressionParserModulus, NegativeModulusPositive) {
    ExpressionParser parser("-7%3");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->toString(), "((-1.000000 * 7.000000) % 3.000000)");
    EXPECT_EQ(ast->evaluate(), 2);
}

TEST(ExpressionParserModulus, PositiveModulusNegative) {
    ExpressionParser parser("7%-3");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 1);
}

TEST(ExpressionParserModulus, NegativeModulusNegative) {
    ExpressionParser parser("-7%-3");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->toString(), "((-1.000000 * 7.000000) % (-1.000000 * 3.000000))");
    EXPECT_EQ(ast->evaluate(), 2);
}

// Failure Case
TEST(ExpressionParserModulus, DivisionByZero) {
    ExpressionParser parser("10%0");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_THROW(
    try { ast->evaluate(); } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "Modulus by zero");
        throw;
    },
    std::runtime_error);
}

/*
 * Full Expressions
 */
TEST(ExpressionParserFullExpression, MultiplicationPrecedence) {
    ExpressionParser parser("2 + 3 * 4 - 1");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 13);
}

TEST(ExpressionParserFullExpression, TwoParenthesisPrecedence) {
    ExpressionParser parser("(2 + 3) * (4 - 1)");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 15);
}

TEST(ExpressionParserFullExpression, OneParenthesisPrecedence) {
    ExpressionParser parser("(2 + 3) * 4 - 1");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 19);
}

TEST(ExpressionParserFullExpression, ExponentialPrecedence) {
    ExpressionParser parser("2 + 2 ^ 2");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 6);
}

TEST(ExpressionParserFullExpression, ExponentialParenthesis) {
    ExpressionParser parser("(2 + 2) ^ 2");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 16);
}

TEST(ExpressionParserFullExpression, ParenthesisExponentialPrecedence) {
    ExpressionParser parser("1 + 2 * (2 + 3)^2");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 51);
}

TEST(ExpressionParserFullExpression, ExponentialPrecedenceOverAdd) {
    ExpressionParser parser("( 2 + 3) ^ 2 + 1");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 26);
}

TEST(ExpressionParserFullExpression, ParenthesisPrecedenceOverExponential) {
    ExpressionParser parser("( 2 + 3) ^ (2 + 1)");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 125);
}

TEST(ExpressionParserFullExpression, LargeExpression) {
    ExpressionParser parser("3 + 2 - 1 / 2 * 4 ^ 2 + 1");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), -2);
}

TEST(ExpressionParserFullExpression, LargeExpressionParenthesis) {
    ExpressionParser parser("3 *( 1 + 2) - (( 4 + 4) * 3) / 2");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), -3);
}

TEST(ExpressionParserFullExpression, NegativeExponent) {
    ExpressionParser parser("2^ -2");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 0.25);
}

TEST(ExpressionParserFullExpression, ModPrecedence) {
    ExpressionParser parser("1 + 3 % 2");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 2);
}

TEST(ExpressionParserFullExpression, ModPrecedenceParenthesis) {
    ExpressionParser parser("(1 + 3) % 2");
    std::unique_ptr<ASTNode> ast = parser.parse();
    EXPECT_EQ(ast->evaluate(), 0);
}

// Failures
TEST(ExpressionParserFullExpression, EnclosedEmptyParenthesisAfter) {
    ExpressionParser parser("(1 + 1 ())");
    EXPECT_THROW(
        try { parser.parse(); } catch (const std::runtime_error& e) {
            EXPECT_STREQ(e.what(), "Expected closing parenthesis, received: (");
            throw;
        },
        std::runtime_error);
}

TEST(ExpressionParserFullExpression, EmptyParenthesisAfter) {
    ExpressionParser parser("1 + 1 ()");
    EXPECT_THROW(
        try { parser.parse(); } catch (const std::runtime_error& e) {
            EXPECT_STREQ(e.what(), "Expected an operator, received: (");
            throw;
        },
        std::runtime_error);
}

TEST(ExpressionParserFullExpression, EnclosedEmptyParenthesisBefore) {
    ExpressionParser parser("(() 2 - 1)");
    EXPECT_THROW(
        try { parser.parse(); } catch (const std::runtime_error& e) {
            EXPECT_STREQ(e.what(), "Empty parenthesis");
            throw;
        },
        std::runtime_error);
}

TEST(ExpressionParserFullExpression, EmptyParenthesisBefore) {
    ExpressionParser parser("() 2 - 1");
    EXPECT_THROW(
        try { parser.parse(); } catch (const std::runtime_error& e) {
            EXPECT_STREQ(e.what(), "Empty parenthesis");
            throw;
        },
        std::runtime_error);
}

TEST(ExpressionParserFullExpression, MismatchedParenthesisBefore) {
    ExpressionParser parser("(1 + 1");
    EXPECT_THROW(
        try { parser.parse(); } catch (const std::runtime_error& e) {
            EXPECT_STREQ(e.what(), "Expected closing parenthesis, received: \\0 (end of expression)");
            throw;
        },
        std::runtime_error);
}

TEST(ExpressionParserFullExpression, MismatchedParenthesisBeforeSpaced) {
    ExpressionParser parser("(1 + 1");
    EXPECT_THROW(
        try { parser.parse(); } catch (const std::runtime_error& e) {
            EXPECT_STREQ(e.what(), "Expected closing parenthesis, received: \\0 (end of expression)");
            throw;
        },
        std::runtime_error);
}

TEST(ExpressionParserFullExpression, MismatchedParenthesisAfter) {
    ExpressionParser parser("1 + 1)");
    EXPECT_THROW(
        try { parser.parse(); } catch (const std::runtime_error& e) {
            EXPECT_STREQ(e.what(), "Missing opening parenthesis");
            throw;
        },
        std::runtime_error);
}

TEST(ExpressionParserFullExpression, MismatchedParenthesisAfterSpaced) {
    ExpressionParser parser("1 + 1 )");
    EXPECT_THROW(
        try { parser.parse(); } catch (const std::runtime_error& e) {
            EXPECT_STREQ(e.what(), "Missing opening parenthesis");
            throw;
        },
        std::runtime_error);
}
