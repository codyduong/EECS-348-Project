// tests/test_ASTNode.cpp
#include <gtest/gtest.h>
#include "ASTNode.h"

// Test NumberNode
TEST(NumberNodeTest, Evaluate) {
    NumberNode numNode(42.0);
    EXPECT_DOUBLE_EQ(numNode.evaluate(), 42.0);
}

TEST(NumberNodeTest, ToString) {
    NumberNode numNode(42.0);
    EXPECT_EQ(numNode.toString(), "42.000000");
}

// Test BinaryOperationNode
TEST(BinaryOperationNodeTest, AdditionEvaluate) {
    NumberNode left(20.0);
    NumberNode right(22.0);
    BinaryOperationNode evaluate('+', std::make_unique<NumberNode>(left), std::make_unique<NumberNode>(right));
    EXPECT_DOUBLE_EQ(addNode.evaluate(), 42.0);
}

TEST(BinaryOperationNodeTest, AdditionToString) {
    NumberNode left(20.0);
    NumberNode right(22.0);
    BinaryOperationNode evaluate('+', std::make_unique<NumberNode>(left), std::make_unique<NumberNode>(right));
    EXPECT_EQ(addNode.toString(), "(20.000000 + 22.000000)");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}