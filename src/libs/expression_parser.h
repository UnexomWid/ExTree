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

BinaryTree* toExpressionTree(Queue postfix);

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
 * Evaluates a postfix expression.
 *
 * If the postfix expression contains variables (i.e. non-numeric operands), they are automatically
 * replaced with the default value, 0.
 *
 * @param postfix The postfix expression to evaluate, as a queue of operands and operators.
 *
 * @return The result of the postfix expression, if it is valid. Otherwise, the last element of
 * the expression stack.
 */
double evalPostfix(Queue postfix);
/**
 * Evaluates a postfix expression.
 *
 * If the postfix expression contains variables (i.e. non-numeric operands), they are automatically
 * replaced with the default value, 0.
 *
 * @param postfix The postfix expression to evaluate, as an array of characters which contains
 * operands and operators separated by space.
 *
 * @return The result of the postfix expression, if it is valid. Otherwise, the last element of
 * the expression stack.
 */
double evalPostfix(const char* postfix);
/**
 * Evaluates a postfix expression, and substitutes a group of variables with a group of values.
 *
 * If the postfix expression contains variables (i.e. non-numeric operands) that cannot be substituted
 * (i.e. they do not exist in the array of variables), they are automatically replaced with the
 * default value, 0.
 *
 * @param postfix The postfix expression to evaluate, as a queue of operands and operators.
 * @param variables The variables to substitute.
 * @param values The values with which to substitute the variables.
 * @param count The number of elements the variables array contains.
 *
 * @return The result of the postfix expression, if it is valid. Otherwise, the last element of
 * the expression stack.
 */
double evalPostfix(Queue postfix, const std::string* variables, const double* values, uint32_t count);
/**
 * Evaluates a postfix expression, and substitutes a group of variables with a group of values.
 *
 * If the postfix expression contains variables (i.e. non-numeric operands) that cannot be substituted
 * (i.e. they do not exist in the array of variables), they are automatically replaced with the
 * default value, 0.
 *
 * @param postfix The postfix expression to evaluate, as an array of characters which contains
 * operands and operators separated by space.
 * @param variables The variables to substitute.
 * @param values The values with which to substitute the variables.
 * @param count The number of elements the variables array contains.
 *
 * @return The result of the postfix expression, if it is valid. Otherwise, the last element of
 * the expression stack.
 */
double evalPostfix(const char* postfix, const std::string* variables, const double* values, uint32_t count);

/**
 * Evaluates an infix expression.
 *
 * If the infix expression contains variables (i.e. non-numeric operands), they are automatically
 * replaced with the default value, 0.
 *
 * @param infix The infix expression to evaluate, as an array of characters.
 *
 * @return The result of the infix expression, if it is valid. Otherwise, the last element of
 * the expression stack.
 */
double evalInfix(const char* infix);
/**
 * Evaluates an infix expression, and substitutes a group of variables with a group of values.
 *
 * If the infix expression contains variables (i.e. non-numeric operands) that cannot be substituted
 * (i.e. they do not exist in the array of variables), they are automatically replaced with the
 * default value, 0.
 *
 * @param infix The infix expression to evaluate, as an array of characters.
 * @param variables The variables to substitute.
 * @param values The values with which to substitute the variables.
 * @param count The number of elements the variables array contains.
 *
 * @return The result of the infix expression, if it is valid. Otherwise, the last element of
 * the expression stack.
 */
double evalInfix(const char* infix, const std::string* variables, const double* values, uint32_t count);

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
