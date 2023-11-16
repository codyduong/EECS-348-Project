// ExpressionParser.cpp
#include "ExpressionParser.h"
#include <cctype>

ExpressionParser::ExpressionParser(const std::string& expression) : expression(expression), pos(0) {}

//call this after the parser gets to the left number of the AST to get the operator
char ExpressionParser::getNextToken() {
    while (pos < expression.size() && std::isspace(expression[pos])) {
        ++pos;  // Skip whitespaces
    }
    if (pos >= expression.size()) {
        return '\0';  // End of expression
    }
    return expression[pos++];
    }

std::unique_ptr<ASTNode> ExpressionParser::parseNumber()  {
    size_t startPos = pos;
    while (pos < expression.size() && (std::isdigit(expression[pos]) || expression[pos] == '.')) { //this while statement might be able to be simplified
        ++pos;
    }
    std::string numStr = expression.substr(startPos, pos - startPos);
    return std::make_unique<NumberNode>(std::stod(numStr));
    }

std::unique_ptr<ASTNode> ExpressionParser::parseTerm() {
    /*parseTerm is for whatever is being added or subtracted together and
    parseFactor can be used for whatever is being multiplied and divided.
    The AST will evaluate everything in the order it is created but it is kind of backwards
    parseTerm is called first becuase the addition and subtraction will be evaluated last*/
    //auto left = parseFactor();
    auto left = parseNumber();
    while (true) {
        char op = getNextToken();
        if (op != '*' && op != '/') {
            pos--;  // Put back the token if it's not a '*' or '/'
            break;
        }
        //auto right = parseFactor();
        auto right = parseNumber();
        left = std::make_unique<BinaryOpNode>(op, std::move(left), std::move(right));
        }
    return left;
    }

/*
    std::unique_ptr<ASTNode> ExpressionParser::parseFactor() {
        return left;
    }
*/

/*
will lastly have to create a similar function to parseFactor and parseTerm 
that first check for parentheses and do all of the operations inside the parentheses in the order of operations
before evaluating everything else
*/

std::unique_ptr<ASTNode> ExpressionParser::parse() {
    return parseTerm();
}
