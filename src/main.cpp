#include <iostream>
#include "ExpressionParser.h"

int main() {
    std::string expression = "3 + (4 * 2 - 7) / 5 % 3";
    ExpressionParser parser(expression);
    std::unique_ptr<ASTNode> ast = parser.parse();
    std::cout << "Expression: " << expression << std::endl;
    std::cout << "Result: " << ast->evaluate() << std::endl;
    std::cout << "AST: " << ast->toString() << std::endl;

    return 0;
}