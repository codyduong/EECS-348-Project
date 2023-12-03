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

std::unique_ptr<ASTNode> ExpressionParser::parseNumber() {
    size_t startPos = pos;
    while (pos < expression.size() && (std::isdigit(expression[pos]) || expression[pos] == '.')) {
        ++pos;
    }
    // It is possible we have encountered an invalid character, manually increment by one if the case, to get
    // correct expression substr, but invalid numStr. Catch it in the try catch below.
    if (pos == startPos) {
        ++pos;
    }

    std::string numStr = expression.substr(startPos, pos - startPos);
    try {
        return std::make_unique<NumberNode>(std::stod(numStr));
    } catch (const std::invalid_argument& e) {
        // Catch the invalid argument here
        throw std::runtime_error("Expected a number, received: " + numStr);
    }
}

std::unique_ptr<ASTNode> ExpressionParser::parseFactor() {
    char currentToken = getNextToken();

    if (currentToken == '(') {
        auto expressionInsideParentheses = parseExpression();
        if (getNextToken() != ')') {
            throw std::runtime_error("Missing closing parenthesis");
        }
        return expressionInsideParentheses;
    } else if (currentToken == '-') {
        // Handle unary minus
        auto factor = parseFactor();
        // We don't have UnaryNodes, but -1 * the factor is equivalent.
        return std::make_unique<BinaryOperationNode>('*', std::make_unique<NumberNode>(-1), std::move(factor));
    } else {
        pos--;  // Put back the token if it's not an opening parenthesis
        return parseNumber();
    }
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
        left = std::make_unique<BinaryOperationNode>(op, std::move(left), std::move(right));
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

std::unique_ptr<ASTNode> ExpressionParser::parse() { return parseExpression(); }
