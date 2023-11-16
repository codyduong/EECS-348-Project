// ASTNode.cpp
#include "ASTNode.h"

BinaryOperationNode::BinaryOperationNode(char op, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
    : op(op), left(std::move(left)), right(std::move(right)) {}

double BinaryOperationNode::evaluate() const {
    double leftVal = left->evaluate();
    double rightVal = right->evaluate();
    switch (op) {
        case '+': return leftVal + rightVal;
        //add in cases for the other operators
        //add in error handling for operations like division cannot divide by zero
        default: throw std::runtime_error("Invalid operator");
    }
}

NumberNode::NumberNode(double value) : value(value) {}

double NumberNode::evaluate() const {
    return value;
}

std::string NumberNode::toString() const {
    return std::to_string(value);
}

std::string BinaryOperationNode::toString() const {
    return "(" + left->toString() + " " + op + " " + right->toString() + ")";
}