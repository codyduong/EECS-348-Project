#include <iostream>
#include <regex>

#include "ExpressionParser.h"
#include "version.hpp"

int handleInput(std::string inputExpression, bool debugFlag) {
    try {
        ExpressionParser parser(inputExpression);
        std::unique_ptr<ASTNode> result = parser.parse();
        double evaluationResult = result->evaluate();

        if (debugFlag) {
            std::cout << "Expression: " << inputExpression << std::endl;
            std::cout << "Result: " << evaluationResult << std::endl;
            std::cout << "AST: " << result->toString() << std::endl;
        } else {
            std::cout << evaluationResult << std::endl;
        }
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}

int main(int argc, char* argv[]) {
    bool loopFlag = false;
    bool versionFlag = false;
    bool debugFlag = false;
    std::string inputExpression;

    if (argc >= 1) {
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];

            if (arg == "-v" || arg == "--version") {
                versionFlag = true;
            } else if (arg == "-c" || arg == "--continuous") {
                loopFlag = true;
            } else if (arg == "-d" || arg == "--debug") {
                loopFlag = true;
                // check if we are - or -- started followed by letters, otherwise parse as input
            } else if (std::regex_match(arg, std::regex("^--?[a-zA-Z]+$"))) {
                std::cerr << "Error: \n\tinvalid flag: " << arg << std::endl;
                return 1;
            } else {
                // if we already set the inputExpression we messed up somewhere
                if (!inputExpression.empty()) {
                    std::cerr << "Unexpected argument: " << arg << std::endl;
                    return 1;
                }
                inputExpression = arg;
            }
        }
    }

    // version is absorbing, ie. will prevent any other interaction
    if (versionFlag) {
        std::cout << "Version " << PROJECT_VERSION_MAJOR << "." << PROJECT_VERSION_MINOR << "."
                  << PROJECT_VERSION_PATCH;

        if (PROJECT_VERSION_RC > 0) {
            std::cout << "-rc" << PROJECT_VERSION_RC;
        }

        std::cout << std::endl;
        return 0;
    }

    if (!inputExpression.empty() && loopFlag) {
        std::cerr
            << "-c/--configuration flag is mutually exclusive with an arithmetic input. Please specify one or the other."
            << std::endl;
        return 1;
    }

    // expect an input or the -c flag
    if (!loopFlag) {
        if (inputExpression.empty()) {
            std::cerr << "Expected an input expression:" << std::endl
                      << "\tIf wanting to input continuous expressions with prompts, use the -c or --c continuous flag"
                      << std::endl
                      << "\tOtherwise pass in an arithmetic expression to be evaluated" << std::endl;
            return 1;
        } else {
            return handleInput(inputExpression, debugFlag);
        }
    }

    while (loopFlag) {
        std::cout << "Enter an arithmetic expression (type 'quit', 'exit', or press CTRL+D to exit loop): ";
        if (!std::getline(std::cin, inputExpression) || inputExpression == "quit" || inputExpression == "q" ||
            inputExpression == "quit()" || inputExpression == "exit" || inputExpression == "exit()") {
            break;
        }
        handleInput(inputExpression, debugFlag);
    }

    return 0;
}
