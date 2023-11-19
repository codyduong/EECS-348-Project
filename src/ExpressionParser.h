// ExpressionParser.h
#pragma once

#include <memory>
#include <stdexcept>
#include "ASTNode.h"

// ExpressionParser class for parsing algebraic expressions.
class ExpressionParser {
private:
    const std::string expression;  // Changed from reference to object
    size_t pos;
    char getNextToken();
    std::unique_ptr<ASTNode> parseNumber();
    std::unique_ptr<ASTNode> parseTerm();
    std::unique_ptr<ASTNode> parseFactor();
    std::unique_ptr<ASTNode> parseExpression();
    std::unique_ptr<ASTNode> createBinaryOperationNode(char op, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right);

public:
    explicit ExpressionParser(const std::string& expression);
    std::unique_ptr<ASTNode> parse();
};
