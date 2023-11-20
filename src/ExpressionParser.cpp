#include "ExpressionParser.h"
#include <cctype>
#include <cmath>

ExpressionParser::ExpressionParser(const std::string& expression) : expression(expression), pos(0) {}

char ExpressionParser::getNextToken() {
    while (pos < expression.size() && std::isspace(expression[pos])) {
        ++pos;  // Skip whitespaces
    }
    if (pos >= expression.size()) {
        return '\0';  // End of expression
    }
    return expression[pos++];
}

std::unique_ptr<ASTNode> ExpressionParser::createBinaryOperationNode(char op, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right) {
    return std::make_unique<BinaryOperationNode>(op, std::move(left), std::move(right));
}

std::unique_ptr<ASTNode> ExpressionParser::parseNumber() {
    size_t startPos = pos;
    while (pos < expression.size() && (std::isdigit(expression[pos]) || expression[pos] == '.' || expression[pos] == '-' || expression[pos] == '+')) {
        ++pos;
    }
    std::string numStr = expression.substr(startPos, pos - startPos);
    return std::make_unique<NumberNode>(std::stod(numStr));
}

std::unique_ptr<ASTNode> ExpressionParser::parseFactor() {
    char currentToken = getNextToken();

    if (currentToken == '(') {
        auto expressionInsideParentheses = parseExpression();
        if (getNextToken() != ')') {
            throw std::runtime_error("Missing closing parenthesis");
        }
        return expressionInsideParentheses;
    } else {
        pos--; // Put back the token if it's not an opening parenthesis
        return parseNumber();
    }
}
std::cout << "Current Token in parseTerm: " << op << std::endl;

std::unique_ptr<ASTNode> ExpressionParser::parseTerm() {
    auto left = parseFactor();

    while (true) {
        char op = getNextToken();
        if (op != '*' && op != '/' && op != '%' && op != '^') {
            pos--; // Put back the token if it's not one of the recognized operators
            break;
        }

        // Add this debugging statement
        std::cout << "Operator: " << op << std::endl;

        auto right = parseFactor();
        switch (op) {
            case '*':
            case '/':
            case '%':
            case '^':
                left = createBinaryOperationNode(op, std::move(left), std::move(right));
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
            pos--; // Put back the token if it's not a '+' or '-'
            break;
        }
        auto right = parseTerm();
        left = createBinaryOperationNode(op, std::move(left), std::move(right));
    }
    return left;
}

std::unique_ptr<ASTNode> ExpressionParser::parse() {
    return parseExpression();
}
