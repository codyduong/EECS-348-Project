// ASTNode.h
#pragma once

#include <memory>
#include <stdexcept>
#include <string>

// Abstract base class for AST nodes.
class ASTNode {
   public:
    // Evaluate the AST node.
    virtual ~ASTNode() = default;
    virtual double evaluate() const = 0;

    // Convert the AST node to a string for debugging.
    virtual std::string toString() const = 0;
};

// Node for binary operations (e.g., +, -, *, /, %).
// Consists of a left value, an operator (op) and right value.
class BinaryOperationNode : public ASTNode {
   public:
    BinaryOperationNode(char op, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right);
    double evaluate() const override;
    std::string toString() const override;

   private:
    char op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
};

// Node for representing numeric values.
class NumberNode : public ASTNode {
   public:
    explicit NumberNode(double value);
    double evaluate() const override;
    std::string toString() const override;

   private:
    double value;
};
