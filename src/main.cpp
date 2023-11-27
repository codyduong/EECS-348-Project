#include <iostream>

#include "ExpressionParser.h"
#include "version.hpp"

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string arg = argv[1];

        // Check for help or version flags
        if (arg == "-h" || arg == "--help") {
            std::cout << "Help message here..." << std::endl;
            return 0;
        } else if (arg == "-v" || arg == "--version") {
            std::cout << "Version " << PROJECT_VERSION_MAJOR << "." << PROJECT_VERSION_MINOR << "."
                      << PROJECT_VERSION_PATCH;

            if (PROJECT_VERSION_RC > 0) {
                std::cout << "-rc" << PROJECT_VERSION_RC;
            }

            std::cout << std::endl;
            return 0;
        }
    }

    std::cout << "Enter an algebraic expression: ";
    std::string inputExpression;
    std::getline(std::cin, inputExpression);

    try {
        ExpressionParser parser(inputExpression);
        std::unique_ptr<ASTNode> result = parser.parse();
        double evaluationResult = result->evaluate();

        std::cout << "Expression: " << inputExpression << std::endl;
        std::cout << "Result: " << evaluationResult << std::endl;
        std::cout << "AST: " << result->toString() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
