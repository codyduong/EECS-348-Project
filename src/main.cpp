#include <iostream>
#include "ExpressionParser.h"

int main() {
    std::string expression = "1+1";
    //These are valid expressions: "1+1" , "1 +1" but "1 + 1" is not valid the ExpressionParser::parseNumber function does not account for whitespace correctly
    //eventually add in user input instead of hard coding expression
    ExpressionParser parser(expression); //creates ExpressionParser class with the givin input expression. The expression is stored as a member variable callded: expression
    auto ast = parser.parse(); //this creates a variable ast that is a result of the ExpressionParser class
    double result = ast->evaluate();
    std::cout << "Expression: " << expression << std::endl;
    std::cout << "Result: " << result << std::endl;
    std::cout << "AST: " << ast->toString() << std::endl;
    //Add in error handling here try/except block with runtime error

    // std::cout << "Enter an algebraic expression: ";
    // std::string inputExpression;
    // std::getline(std::cin, inputExpression);

    // try {
    //     ExpressionParser parser(inputExpression);
    //     std::unique_ptr<ASTNode> result = parser.parse();
    //     std::cout << "Result: " << result->evaluate() << std::endl;
    // } catch (const std::exception& e) {
    //     std::cerr << "Error: " << e.what() << std::endl;
    // }

    return 0;
}
