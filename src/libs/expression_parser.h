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

bool isOperator(const std::string &token);

bool isOperand(const std::string &token);

bool isFunction(const std::string &token);

bool isConstant(const std::string &token);

bool isUnaryFunction(const std::string &token);

bool isBinaryFunction(const std::string &token);

bool isUnaryOperator(const std::string &token);

bool isBinaryOperator(const std::string &token);

unsigned short getPrecedence(const std::string &token);


/**
 * Converts an expression from infix notation to postfix notation.
 *
 * @param infix The infix notation of the expression.
 *
 * @return The postfix notation of the expression, as a queue. Each element
 * of the queue represents either an operand or an operator.
 */
Queue toPostfix(const char* infix, std::string &error, unsigned int &errorIndex);

BinaryTree* toExpressionTree(Queue postfix);

double evalUnaryOperator(const std::string &op, double argument, std::string &error);

double evalBinaryOperator(const std::string &op, double left, double right, std::string &error);

double evalUnaryFunction(const std::string &function, double argument, std::string &error);

double evalBinaryFunction(const std::string &function, double left, double right, std::string &error);

double evalExpressionTree(BinaryTree* tree, std::string &error);

/**
 * Substitutes a group of variables in an expression with a group of values.
 *
 * If a a variable does not exist nt the expression, it will simply be ignored.
 * The arrays of variables and values have the same indices. That is, the first element
 * of the array of values corresponds to the first element of the array of variables. The
 * array of values must not contain less elements than the array of variables.
 *
 * @param expression The expression where to substitute the variables, as a queue of operands
 * and operators.
 * @param variables The variables to substitute.
 * @param values The values with which to substitute the variables.
 * @param count The number of elements the variables array contains.
 *
 * @return A new expression where the variables have been substituted, as a queue of operands
 * and operators.
 */
Queue substitute(Queue expression, const std::string* variables, const double* values, uint32_t count);

/**
 * Substitutes a group of variables in an expression with a group of values.
 *
 * If a a variable does not exist nt the expression, it will simply be ignored.
 * The arrays of variables and values have the same indices. That is, the first element
 * of the array of values corresponds to the first element of the array of variables. The
 * array of values must not contain less elements than the array of variables.
 *
 * @param expression The expression where to substitute the variables.
 * @param variables The variables to substitute.
 * @param values The values with which to substitute the variables.
 * @param count The number of elements the variables array contains.
 *
 * @return A new expression where the variables have been substituted.
 */
char* substitute(const char* expression, const std::string* variables, const double* values, uint32_t count);

/**
 * Serializes a postfix expression, stored as a queue of operands and operators.
 *
 * The queue of operands and operators is converted to an array of characters, which contains
 * the operands and operators separated by space, and represents the same postfix expression.
 *
 * @param postfix The postfix expression.
 *
 * @return The serialized postfix expression, if the queue is not empty. Otherwise, nullptr.
 */
char* serializePostfix(Queue postfix);

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
Queue deserializePostfix(const char* infix);

#endif // EXPRESSION_PARSER_H_INCLUDED
