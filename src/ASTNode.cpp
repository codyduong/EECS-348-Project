// ASTNode.cpp
#include "ASTNode.h"

#include <cmath>

BinaryOperationNode::BinaryOperationNode(char op, std::unique_ptr<ASTNode> left,
                                         std::unique_ptr<ASTNode> right)
    : op(op), left(std::move(left)), right(std::move(right)) {}

double BinaryOperationNode::evaluate() const {
    double leftVal = left->evaluate();
    double rightVal = right->evaluate();
    switch (op) {
        case '+':
            return leftVal + rightVal;
        case '-':
            return leftVal - rightVal;
        case '*':
            return leftVal * rightVal;
        case '/':
            if (rightVal != 0.0) {
                return leftVal / rightVal;
            } else {
                throw std::runtime_error("Division by zero");
            }
        case '%':
            if (rightVal != 0.0) {
                return std::fmod(leftVal, rightVal);
            } else {
                throw std::runtime_error("Modulus by zero");
            }
        case '^':
            return std::pow(leftVal, rightVal);

        default:
            throw std::runtime_error("Invalid operator");
    }
}

NumberNode::NumberNode(double value) : value(value) {}

double NumberNode::evaluate() const { return value; }

std::string NumberNode::toString() const { return std::to_string(value); }

std::string BinaryOperationNode::toString() const {
    return "(" + left->toString() + " " + op + " " + right->toString() + ")";
}