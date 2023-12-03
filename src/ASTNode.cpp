// ASTNode.cpp
#include "ASTNode.h"

#include <stdlib.h>

#include <cmath>

BinaryOperationNode::BinaryOperationNode(char op, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
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
                double result = std::fmod(leftVal, rightVal);

                // Always make modulus be positive, makes writing test cases easier, inline with math definition
                // View on wikipedia: https://en.wikipedia.org/wiki/Modulo#Variants_of_the_definition
                //  > This still leaves a sign ambiguity if the remainder is non-zero: two possible choices for the
                //  remainder occur, one negative and the other positive, and two possible choices for the quotient
                //  occur.
                //  > In number theory, the positive remainder is always chosen...
                if (result < 0) {
                    result += std::abs(rightVal);
                }
                return result;
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