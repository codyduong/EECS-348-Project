// ExpressionParser.h
#pragma once

#include <memory>
#include <stdexcept>
#include "ASTNode.h"

// ExpressionParser class for parsing algebraic expressions.
class ExpressionParser {
private:
    const std::string& expression;
    size_t pos;
    char getNextToken();
    std::unique_ptr<ASTNode> parseNumber();
    std::unique_ptr<ASTNode> parseTerm();
    std::unique_ptr<ASTNode> parseFactor();

public:
    explicit ExpressionParser(const std::string& expression);
    std::unique_ptr<ASTNode> parse();
};
