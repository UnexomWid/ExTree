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

/// Returns the value of a constant.
double getConstantValue(const std::string &token);

/// Returns the precedence value of an operator. Lower values mean higher priority.
ushort getOperatorPrecedence(const std::string &token);

/// Converts an infix expression to postfix. Any errors are stored in the 'error' parameter.
Queue toPostfix(const char* infix, std::string &error, uint &errorIndex);

/// Converts a postfix expression to a binary expression tree.
BinaryTree* toExpressionTree(Queue postfix);

/// Evaluates an unary operator. Any errors are stored in the 'error' parameter.
double evalUnaryOperator(const std::string &op, double argument, std::string &error);

/// Evaluates a binary operator. Any errors are stored in the 'error' parameter.
double evalBinaryOperator(const std::string &op, double left, double right, std::string &error);

/// Evaluates an unary function. Any errors are stored in the 'error' parameter.
double evalUnaryFunction(const std::string &function, double argument, std::string &error);

/// Evaluates a binary function. Any errors are stored in the 'error' parameter.
double evalBinaryFunction(const std::string &function, double left, double right, std::string &error);

/// Evaluates a binary expression tree. Any errors are stored in the 'error' parameter.
double evalExpressionTree(BinaryTree* tree, std::string &error);

/// Substitutes a variable with a value in an expression tree.
void substitute(BinaryTree* &tree, const std::string &variable, double value);

/// Substitutes all constants with their values in an expression tree.
void substituteConstants(BinaryTree* &tree);

/// Converts a postfix expression stored in a Queue to a string.
char* postfixToString(Queue postfix);

#endif // EXPRESSION_PARSER_H_INCLUDED
