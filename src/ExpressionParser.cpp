// ExpressionParser.cpp
#include "ExpressionParser.h"
#include <cctype>
#include <cmath> 

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

std::unique_ptr<ASTNode> ExpressionParser::parseFactor() {
    auto left = parseNumber();
    while (true) {
        char op = getNextToken();
        if (op != '*' && op != '/' && op != '%' && op != '^') {
            pos--;  // Put back the token if it's not one of the recognized operators
            break;
        }
        auto right = parseNumber();
        switch (op) {
            case '*':
                left = std::make_unique<BinaryOperationNode>(op, std::move(left), std::move(right));
                break;
            case '/':
                left = std::make_unique<BinaryOperationNode>(op, std::move(left), std::move(right));
                break;
            case '%':
                left = std::make_unique<BinaryOperationNode>(op, std::move(left), std::move(right));
                break;
            case '^':
                left = std::make_unique<BinaryOperationNode>(op, std::move(left), std::move(right));
                break;
        }
    }
    return left;
}

std::unique_ptr<ASTNode> ExpressionParser::parseTerm() {
    auto left = parseFactor();
    while (true) {
        char op = getNextToken();
        if (op != '*' && op != '/' && op != '%' && op != '^') {
            pos--;  // Put back the token if it's not one of the recognized operators
            break;
        }
        auto right = parseFactor();
        switch (op) {
            case '*':
                left = std::make_unique<BinaryOperationNode>(op, std::move(left), std::move(right));
                break;
            case '/':
                left = std::make_unique<BinaryOperationNode>(op, std::move(left), std::move(right));
                break;
            case '%':
                left = std::make_unique<BinaryOperationNode>(op, std::move(left), std::move(right));
                break;
            case '^':
                left = std::make_unique<BinaryOperationNode>(op, std::move(left), std::move(right));
                break;
        }
    }
    return left;
}

std::unique_ptr<ASTNode> ExpressionParser::parseExpression() {
    auto left = parseTerm();
    while (true) {
        char op = getNextToken();
        if (op != '+' && op != '-') {
            pos--;  // Put back the token if it's not a '+' or '-'
            break;
        }
        auto right = parseTerm();
        left = std::make_unique<BinaryOperationNode>(op, std::move(left), std::move(right));
    }
    return left;
}

std::unique_ptr<ASTNode> ExpressionParser::parse() {
    return parseExpression();
}
