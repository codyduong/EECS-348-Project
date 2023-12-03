#include <gtest/gtest.h>

#include "../src/ASTNode.h"

// Test NumberNode
TEST(NumberNodeTest, Evaluate) {
    NumberNode numNode(42.0);
    EXPECT_DOUBLE_EQ(numNode.evaluate(), 42.0);
}

TEST(NumberNodeTest, ToString) {
    NumberNode numNode(42.0);
    EXPECT_EQ(numNode.toString(), "42.000000");
}

// Test BinaryOperationNode Addition
TEST(BinaryOperationNodeAddition, AdditionEvaluate) {
    NumberNode left(20.0);
    NumberNode right(22.0);
    BinaryOperationNode node('+', std::make_unique<NumberNode>(left), std::make_unique<NumberNode>(right));
    EXPECT_DOUBLE_EQ(node.evaluate(), 42.0);
}

TEST(BinaryOperationNodeAddition, AdditionEvaluateDecimal) {
    NumberNode left(5.5);
    NumberNode right(7.33);
    BinaryOperationNode node('+', std::make_unique<NumberNode>(left), std::make_unique<NumberNode>(right));
    EXPECT_DOUBLE_EQ(node.evaluate(), 12.83);
}

TEST(BinaryOperationNodeAddition, AdditionNegative1) {
    NumberNode left(20.0);
    NumberNode right(-22.0);
    BinaryOperationNode node('+', std::make_unique<NumberNode>(left), std::make_unique<NumberNode>(right));
    EXPECT_DOUBLE_EQ(node.evaluate(), -2);
}

TEST(BinaryOperationNodeAddition, AdditionNegative2) {
    NumberNode left(-20.0);
    NumberNode right(22.0);
    BinaryOperationNode node('+', std::make_unique<NumberNode>(left), std::make_unique<NumberNode>(right));
    EXPECT_DOUBLE_EQ(node.evaluate(), 2);
}

TEST(BinaryOperationNodeAddition, AdditionNegative3) {
    NumberNode left(-20.0);
    NumberNode right(-22.0);
    BinaryOperationNode node('+', std::make_unique<NumberNode>(left), std::make_unique<NumberNode>(right));
    EXPECT_DOUBLE_EQ(node.evaluate(), -42);
}

TEST(BinaryOperationNodeAddition, AdditionToString) {
    NumberNode left(20.0);
    NumberNode right(22.0);
    BinaryOperationNode node('+', std::make_unique<NumberNode>(left), std::make_unique<NumberNode>(right));
    EXPECT_EQ(node.toString(), "(20.000000 + 22.000000)");
}

// Test BinaryOperationNode Subtraction


// Test BinaryOperationNode Multiplication

TEST(BinaryOperationNodeMultiplication, MultiplicationEvaluate) {
    NumberNode left(6.0);
    NumberNode right(7.0);
    BinaryOperationNode node('*', std::make_unique<NumberNode>(left), std::make_unique<NumberNode>(right));
    EXPECT_DOUBLE_EQ(node.evaluate(), 42.0);
}

TEST(BinaryOperationNodeMultiplication, MultiplicationEvaluateDecimal) {
    NumberNode left(0.1);
    NumberNode right(0.2);
    BinaryOperationNode node('*', std::make_unique<NumberNode>(left), std::make_unique<NumberNode>(right));
    EXPECT_DOUBLE_EQ(node.evaluate(), 0.02);
}

TEST(BinaryOperationNodeMultiplication, MultiplicationNegative1) {
    NumberNode left(6.0);
    NumberNode right(-7.0);
    BinaryOperationNode node('*', std::make_unique<NumberNode>(left), std::make_unique<NumberNode>(right));
    EXPECT_DOUBLE_EQ(node.evaluate(), -42.0);
}

TEST(BinaryOperationNodeMultiplication, MultiplicationNegative2) {
    NumberNode left(-6.0);
    NumberNode right(7.0);
    BinaryOperationNode node('*', std::make_unique<NumberNode>(left), std::make_unique<NumberNode>(right));
    EXPECT_DOUBLE_EQ(node.evaluate(), -42.0);
}

TEST(BinaryOperationNodeMultiplication, MultiplicationNegative3) {
    NumberNode left(-6.0);
    NumberNode right(-7.0);
    BinaryOperationNode node('*', std::make_unique<NumberNode>(left), std::make_unique<NumberNode>(right));
    EXPECT_DOUBLE_EQ(node.evaluate(), 42.0);
}

TEST(BinaryOperationNodeMultiplication, MultiplicationToString) {
    NumberNode left(6.0);
    NumberNode right(7.0);
    BinaryOperationNode node('*', std::make_unique<NumberNode>(left), std::make_unique<NumberNode>(right));
    EXPECT_EQ(node.toString(), "(6.000000 * 7.000000)");
}



// Test BinaryOperationNode Division

// Test BinaryOperationNode Modulo
