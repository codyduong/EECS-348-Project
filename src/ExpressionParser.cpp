#include "ExpressionParser.h"
#include <stdexcept>

ExpressionParser::ExpressionParser(const std::string& expression) : expression(expression), pos(0) {}

char ExpressionParser::getNextToken() {
    if (pos < expression.length()) {
        return expression[pos++];
    }
    return '\0';
}

std::unique_ptr<ASTNode> ExpressionParser::parse() {
    return 0;
}