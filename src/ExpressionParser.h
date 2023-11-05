#ifndef EXPRESSIONPARSER_H
#define EXPRESSIONPARSER_H

#include <string>
#include <memory>
#include "ASTNode.h"

// ExpressionParser class for parsing algebraic expressions.
class ExpressionParser {
public:
    ExpressionParser(const std::string& expression);
    std::unique_ptr<ASTNode> parse();
    
private:
    std::string expression;
    size_t pos;

    // Get the next token from the input expression.
    char getNextToken();
};

#endif
