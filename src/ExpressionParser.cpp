#include "ExpressionParser.h"

#include <cctype>
#include <cmath>
#include <string>

ExpressionParser::ExpressionParser(const std::string& expression) : expression(expression), pos(0), leftParenthesis(0) {}

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
        throw std::runtime_error("Expected an expression or number, received: " + numStr);
    }
}

std::unique_ptr<ASTNode> ExpressionParser::parseFactor() {
    char currentToken = getNextToken();

    if (currentToken == '(') {
        leftParenthesis++;
        if (getNextToken() == ')') {
            throw std::runtime_error("Empty parentheses");
        }
        pos--;  // restore the old position
        auto expressionInsideParentheses = parseExpression();
        auto nextToken = getNextToken();

        if (nextToken != ')') {
            // It is possible the nextToken will invalidly list a non useful error message like
            //      FAIL BEHAVIOR -> "(1+1" -> std::runtime_error("Expected closing parenthesis, received: 1")
            //      PASS BEHAVIOR -> "(1+1+)" -> std::runtime_error("Expected closing parenthesis, received: +")
            //      PASS BEHAVIOR -> "(1+1())" -> std::runtime_error("Expected closing parenthesis, received: (")
            //
            //      So instead, double check we aren't at the end of the string as well
            //      PASS BEHAVIOR -> "(1+1" -> std::runtime_error("Expected closing parenthesis, received: \0 (end of expression)") 
            //      PASS BEHAVIOR -> "(1+1+)" -> std::runtime_error("Expected closing parenthesis, received: +")
            //      PASS BEHAVIOR -> "(1+1())" -> std::runtime_error("Expected closing parenthesis, received: (")
            if (nextToken != '\0' && pos != expression.size()) {
                throw std::runtime_error("Expected closing parenthesis, received: " + std::string(1, nextToken));
            } else {
                throw std::runtime_error("Expected closing parenthesis, received: \\0 (end of expression)");
            }
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

std::unique_ptr<ASTNode> ExpressionParser::parseExponentiation() {
    auto left = parseFactor();
    while (true) {
        char op = getNextToken();
        if (op != '^') {
            pos--;  // Put back the token if it's not one of the recognized operators
            break;
        }
        auto right = parseFactor();
        left = std::make_unique<BinaryOperationNode>(op, std::move(left), std::move(right));
    }
    return left;
}

std::unique_ptr<ASTNode> ExpressionParser::parseTerm() {
    auto left = parseExponentiation();
    while (true) {
        char op = getNextToken();
        if (op != '*' && op != '/' && op != '%') {
            pos--;  // Put back the token if it's not one of the recognized operators
            break;
        }
        auto right = parseExponentiation();
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

std::unique_ptr<ASTNode> ExpressionParser::parse() {
    auto result = parseExpression();
    // the pos will be at the last token, ie "1+1" -> '1', so check if increment pos
    // IE. this checks if we have some expression left to parse. That means we received an invalid character,
    // which was discarded, so it meant we expected an operator (the number would've been parsed if it was one).
    if ((++pos < expression.size())) {
        auto lastChar = expression[pos - 1];
        throw std::runtime_error("Expected an operator, received: " + expression.substr(pos - 1, 1));
    }
    // The only way to check if we are mismatched closing parenthesis is to evaluate leftParenthesis vs rightParenthesis
    // Note1: we count leftParenthesis via the parser. It is possible the parser exits early, but it is handled by the above if statement
    // Note2: we don't check missing closing parenthesis heres, just missing opening parenthesis.
    int rightParenthesis = 0;
    for (char c: expression) if (c == ')') rightParenthesis++;
    if (rightParenthesis > leftParenthesis) {
        throw std::runtime_error("Missing opening parenthesis");
    }

    return result;
}
