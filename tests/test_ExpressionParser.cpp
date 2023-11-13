#include "gtest/gtest.h"
#include "ExpressionParser.h"

TEST(ExpressionParser, BasicExpressions) {
    // @codyduong Re-enable once parse is implemented
    // ExpressionParser parser("3 + 2");
    // std::unique_ptr<ASTNode> ast = parser.parse();
    // EXPECT_EQ(ast->evaluate(), 5);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}