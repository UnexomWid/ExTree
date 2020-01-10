/**
 * Expression Parser
 *
 * An implementation of an expression parser that uses Dijkstra's Shunting-yard algorithm to obtain
 * the postfix notation from infix. Also includes functions for postfix and infix evaluation, and
 * for the (de)serialization of postfix expressions.
 *
 * Copyright (c) 2019-2020 Constantin Mihai and Adrian Peterca (https://github.com/UnexomWid/ExTree)
 */
#ifndef EXPRESSION_PARSER_H_INCLUDED
#define EXPRESSION_PARSER_H_INCLUDED

#include <cmath>
#include <string>
#include <cstdint>
#include <cstring>

#include "node.h"
#include "tree.h"
#include "queue.h"
#include "stack.h"
#include "charlib.h"
#include "tree_stack.h"
#include "definitions.h"

bool isOperator(const std::string &token);

bool isOperand(const std::string &token);

bool isFunction(const std::string &token);

bool isConstant(const std::string &token);

bool isUnaryFunction(const std::string &token);

bool isBinaryFunction(const std::string &token);

bool isUnaryOperator(const std::string &token);

bool isBinaryOperator(const std::string &token);

bool isInteger(double value);

double getConstantValue(const std::string &token);

unsigned short getPrecedence(const std::string &token);

Queue toPostfix(const char* infix, std::string &error, unsigned int &errorIndex);

BinaryTree* toExpressionTree(Queue postfix);

double evalUnaryOperator(const std::string &op, double argument, std::string &error);

double evalBinaryOperator(const std::string &op, double left, double right, std::string &error);

double evalUnaryFunction(const std::string &function, double argument, std::string &error);

double evalBinaryFunction(const std::string &function, double left, double right, std::string &error);

double evalExpressionTree(BinaryTree* tree, std::string &error);

void substitute(BinaryTree* &tree, const std::string &variable, double value);

void substituteConstants(BinaryTree* &tree);

char* postfixToString(Queue postfix);

/**
 * Deserializes a postfix expression, stored as an array of characters which contains
 * operands and operators separated by space.
 *
 * The array of characters is converted to queue of operands and operators which
 * and represents the same postfix expression.
 *
 * @param postfix The postfix expression.
 *
 * @return The deserialized postfix expression.
 */
Queue postfixFromString(const char* infix);

#endif // EXPRESSION_PARSER_H_INCLUDED
