#include <iostream>
#include "ExpressionParser.h"

int main() {
    std::cout << "Enter an algebraic expression: ";
    std::string inputExpression;
    std::getline(std::cin, input expression);

    try {
        ExpressionParser parser(input expression);
        std::unique_ptr<ASTNode> result = parser.parse();
        double evaluation result = result->evaluate();

        std::cout << "Expression: " << inputExpression << std::endl;
        std::cout << "Result: " << evaluationResult << std::endl;
        std::cout << "AST: " << result->toString() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
