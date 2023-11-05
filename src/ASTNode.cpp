#include "ASTNode.h"
#include <stdexcept>

NumberNode::NumberNode(double value) : value(value) {}

double NumberNode::evaluate() const {
    return value;
}

std::string NumberNode::toString() const {
    return std::to_string(value);
}

BinaryOperationNode::BinaryOperationNode(char op, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
    : op(op), left(std::move(left)), right(std::move(right)) {}

double BinaryOperationNode::evaluate() const {
    double left_value = left->evaluate();
    double right_value = right->evaluate();

    switch (op) {
        case '+':
            return left_value + right_value;
        default:
            throw std::runtime_error("Invalid operator");
    }
}

std::string BinaryOperationNode::toString() const {
    return "(" + left->toString() + " " + op + " " + right->toString() + ")";
}