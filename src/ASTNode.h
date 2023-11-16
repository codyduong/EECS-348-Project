// ASTNode.h
#pragma once

#include <string>
#include <memory>
#include <stdexcept>

// Abstract base class for AST nodes.
struct ASTNode {
        // Evaluate the AST node.
    virtual ~ASTNode() = default;
    virtual double evaluate() const = 0;

    // Convert the AST node to a string for debugging.
    virtual std::string toString() const = 0;
};

// Node for binary operations (e.g., +, -, *, /, %). 
// Consists of a left value, an operator (op) and right value.
struct BinaryOpNode : public ASTNode {
    char op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    BinaryOpNode(char op, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right);
    double evaluate() const override;
    std::string toString() const override;
};

// Node for representing numeric values.
struct NumberNode : public ASTNode {
    double value;
    explicit NumberNode(double value);
    double evaluate() const override;
    std::string toString() const override;
};
