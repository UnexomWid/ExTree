/**
 * Expression Parser
 *
 * An implementation of an expression parser that uses Dijkstra's Shunting-yard algorithm to obtain
 * the postfix notation from infix. Also includes functions for postfix and infix evaluation, and
 * for the (de)serialization of postfix expressions.
 *
 * Copyright (c) 2019-2020 Constantin Mihai and Adrian Peterca (https://github.com/UnexomWid/ExTree)
 */
#include "expression_parser.h"

bool isOperator(const std::string &token) {
    std::string lowerToken = toLower(token);

    return (lowerToken == "+"     ||
            lowerToken == "-"     ||
            lowerToken == "*"     ||
            lowerToken == "/"     ||
            lowerToken == "neg"   ||
            lowerToken == "="     ||
            lowerToken == "<"     ||
            lowerToken == ">"     ||
            lowerToken == "<="    ||
            lowerToken == ">="    ||
            lowerToken == "<>"    ||
            lowerToken == "or"    ||
            lowerToken == "and"   ||
            lowerToken == "xor"   ||
            lowerToken == "not"   ||
            lowerToken == "mod"   );
}

bool isFunction(const std::string &token) {
    std::string lowerToken = toLower(token);

    return (lowerToken == "abs"           ||
            lowerToken == "acos"          ||
            lowerToken == "asin"          ||
            lowerToken == "atan"          ||
            lowerToken == "atan2"         ||
            lowerToken == "bigmul"        ||
            lowerToken == "ceiling"       ||
            lowerToken == "cos"           ||
            lowerToken == "cosh"          ||
            lowerToken == "exp"           ||
            lowerToken == "floor"         ||
            lowerToken == "ieeeremainder" ||
            lowerToken == "ln"            ||
            lowerToken == "log"           ||
            lowerToken == "log10"         ||
            lowerToken == "max"           ||
            lowerToken == "min"           ||
            lowerToken == "pow"           ||
            lowerToken == "sign"          ||
            lowerToken == "sin"           ||
            lowerToken == "sinh"          ||
            lowerToken == "sqrt"          ||
            lowerToken == "tan"           ||
            lowerToken == "tanh"          ||
            lowerToken == "truncate"      );
}

bool isConstant(const std::string &token) {
    std::string lowerToken = toLower(token);

    return (lowerToken == "e"     ||
            lowerToken == "pi"    ||
            lowerToken == "true"  ||
            lowerToken == "false" );
}

bool isOperand(const std::string &token) {
    return isNumber(token) || (!isOperator(token) &&
                               !isFunction(token) &&
                               !isNullOrWhitespace(token));
}

unsigned short getPrecedence(const std::string &token) {
    std::string lowerToken = toLower(token);

    if(lowerToken == "neg")
        return 1;
    if(lowerToken == "*" || lowerToken == "/")
        return 2;
    if(lowerToken == "\\")
        return 3;
    if(lowerToken == "+" || lowerToken == "-")
        return 4;
    if(lowerToken == "mod")
        return 5;
    if(lowerToken == "=" || lowerToken == "<>" || lowerToken == "<" || lowerToken == "<=" || lowerToken == ">" || lowerToken == ">=")
        return 6;
    if(lowerToken == "not")
        return 7;
    if(lowerToken == "and")
        return 8;
    if(lowerToken == "or")
        return 9;
    if(lowerToken == "xor")
        return 10;

    return 0;
}

bool isUnaryFunction(const std::string &token) {
    std::string lowerToken = toLower(token);

    return (lowerToken == "abs"           ||
            lowerToken == "acos"          ||
            lowerToken == "asin"          ||
            lowerToken == "atan"          ||
            lowerToken == "ceiling"       ||
            lowerToken == "cos"           ||
            lowerToken == "cosh"          ||
            lowerToken == "exp"           ||
            lowerToken == "floor"         ||
            lowerToken == "log"           ||
            lowerToken == "log10"         ||
            lowerToken == "sign"          ||
            lowerToken == "sin"           ||
            lowerToken == "sinh"          ||
            lowerToken == "sqrt"          ||
            lowerToken == "tan"           ||
            lowerToken == "tanh"          ||
            lowerToken == "truncate"      );
}

bool isBinaryFunction(const std::string &token) {
    std::string lowerToken = toLower(token);

    return (lowerToken == "atan2"         ||
            lowerToken == "bigmul"        ||
            lowerToken == "ieeeremainder" ||
            lowerToken == "log"           ||
            lowerToken == "max"           ||
            lowerToken == "min"           ||
            lowerToken == "pow"           );
}

bool isUnaryOperator(const std::string &token) {
    std::string lowerToken = toLower(token);

    return (lowerToken == "neg");
}

bool isBinaryOperator(const std::string &token) {
    std::string lowerToken = toLower(token);

    return (lowerToken == "*"   ||
            lowerToken == "/"   ||
            lowerToken == "\\"  ||
            lowerToken == "+"   ||
            lowerToken == "-"   ||
            lowerToken == "="   ||
            lowerToken == "<>"  ||
            lowerToken == "<"   ||
            lowerToken == "<="  ||
            lowerToken == ">"   ||
            lowerToken == ">="  ||
            lowerToken == "not" ||
            lowerToken == "and" ||
            lowerToken == "or"  ||
            lowerToken == "xor" );
}

bool isInteger(double number) {
    return trunc(number) == number;
}

BinaryTree* toExpressionTree(Queue postfix) {
    TreeStack stack;
    postfix = postfix.copy();

    while(!postfix.empty()) {
        std::string token = toLower(postfix.front());
        postfix.pop();

        if(isOperator(token)) {
            BinaryTree* tree = new BinaryTree;

            if(isUnaryOperator(token)) {
                /* if(token == "neg") {
                 *    tree->data = "-";
                 * } else tree->data = token;*/
                tree->data = token;

                tree->left = stack.top();
                stack.pop();
                tree->right = nullptr;

                stack.push(tree);
            } else {
                tree->data = token;
                tree->right = stack.top();
                stack.pop();
                tree->left = stack.top();
                stack.pop();

                stack.push(tree);
            }
        } else if(isFunction(token)) {
            BinaryTree* tree = new BinaryTree;

            if(isUnaryFunction(token)) {
                tree->data = token;
                tree->left = stack.top();
                stack.pop();
                tree->right = nullptr;

                stack.push(tree);
            } else {
                tree->data = token;
                tree->right = stack.top();
                stack.pop();
                tree->left = stack.top();
                stack.pop();

                stack.push(tree);
            }
        } else if(token.size() > 2 && isFunction(token.substr(0, token.size() - 2))) {
            BinaryTree* tree = new BinaryTree;

            std::string functionType = token.substr(token.size() - 2, 2);

            if(functionType == "_u") {
                tree->data = token.substr(0, token.size() - 2);
                tree->left = stack.top();
                stack.pop();
                tree->right = nullptr;

                stack.push(tree);
            } else if(functionType == "_b") {
                tree->data = token.substr(0, token.size() - 2);
                tree->right = stack.top();
                stack.pop();
                tree->left = stack.top();
                stack.pop();

                stack.push(tree);
            }
        } else if(isOperand(token)) {
            BinaryTree* tree = new BinaryTree;
            tree->data = token;
            tree->right = nullptr;
            tree->left = nullptr;

            stack.push(tree);
        }
    }

    return stack.top();
}

double evalUnaryOperator(const std::string &op, double argument, std::string &error) {
    if(op == "neg") {
        return -argument;
    }

    error = "Unknown unary operator '" + op + "'";
    return 0;
}

double evalBinaryOperator(const std::string &op, double left, double right, std::string &error) {
    if(op == "+") {
        return left + right;
    }
    if(op == "-") {
        return left - right;
    }
    if(op == "*") {
        return left * right;
    }
    if(op == "/") {
        if(right == 0) {
            error = "Cannot divide by 0";
            return 0;
        } else return left / right;
    }
    if(op == "\\") {
        if(right == 0) {
            error = "Cannot divide by 0";
            return 0;
        } else return (int) (left / right);
    }
    if(op == "=") {
        return left == right;
    }
    if(op == "<>") {
        return left != right;
    }
    if(op == "<") {
        return left < right;
    }
    if(op == "<=") {
        return left <= right;
    }
    if(op == ">") {
        return left > right;
    }
    if(op == ">=") {
        return left >= right;
    }
    if(op == "not") {
        if(!isInteger(left)) {
            error = "Cannot apply 'not' operator on floating point number " + toString(left);
            return 0;
        }
        return ~(int) left;
    }
    if(op == "and") {
        if(!isInteger(left) || !isInteger(right)) {
            error = "Cannot apply 'and' operator on floating point numbers " + toString(left) + " and " + toString(right);
            return 0;
        }
        return (int) left & (int) right;
    }
    if(op == "or") {
        if(!isInteger(left) || !isInteger(right)) {
            error = "Cannot apply 'or' operator on floating point numbers " + toString(left) + " and " + toString(right);
            return 0;
        }
        return (int) left | (int) right;
    }
    if(op == "xor") {
        if(!isInteger(left) || !isInteger(right)) {
            error = "Cannot apply 'xor' operator on floating point numbers " + toString(left) + " and " + toString(right);
            return 0;
        }
        return (int) left ^ (int) right;
    }

    error = "Unknown binary operator '" + op + "'";
    return 0;
}

double evalUnaryFunction(const std::string &function, double argument, std::string &error) {
    if(function == "abs") {
        return fabs(argument);
    }
    if(function == "acos") {
        if(argument < -1 || argument > 1) {
            error = "Value " + toString(argument) + " out of range for function 'acos'";
            return 0;
        }
        return acos(argument);
    }
    if(function == "asin") {
        if(argument < -1 || argument > 1) {
            error = "Value " + toString(argument) + " out of range for function 'asin'";
            return 0;
        }
        return asin(argument);
    }
    if(function == "atan") {
        if(argument < -1 || argument > 1) {
            error = "Value " + toString(argument) + " out of range for function 'atan'";
            return 0;
        }
        return atan(argument);
    }
    if(function == "ceil") {
        return ceil(argument);
    }
    if(function == "cos") {
        return cos(argument);
    }
    if(function == "cosh") {
        try {
            return cosh(argument);
        } catch(std::exception &e) {
            error = "Value " + toString(argument) + " is too large for function 'cosh'";
            return 0;
        }
    }
    if(function == "exp") {
        try {
            return exp(argument);
        } catch(std::exception &e) {
            error = "Value " + toString(argument) + " is too large for function 'exp'";
            return 0;
        }
    }
    if(function == "floor") {
        return floor(argument);
    }
    if(function == "log") {
        if(argument <= 0) {
            error = "Value " + toString(argument) + " out of range for unary function 'log'";
            return 0;
        }
        return log(argument);
    }
    if(function == "log10") {
        if(argument <= 0) {
            error = "Value " + toString(argument) + " out of range for function 'log10'";
            return 0;
        }
        return log10(argument);
    }
    if(function == "sign") {
        if(argument == 0)
            return 0;
        if(argument < 0)
            return -1;
        return 1;
    }
    if(function == "sin") {
        return sin(argument);
    }
    if(function == "sinh") {
        try {
            return sinh(argument);
        } catch(std::exception &e) {
            error = "Value " + toString(argument) + " is too large for function 'sinh'";
            return 0;
        }
    }
    if(function == "sqrt") {
        try {
            return sqrt(argument);
        } catch(std::exception &e) {
            error = "Value " + toString(argument) + " cannot be negative for function 'sqrt'";
            return 0;
        }
    }
    if(function == "tan") {
        return tan(argument);
    }
    if(function == "tanh") {
        try {
            return tanh(argument);
        } catch(std::exception &e) {
            error = "Value " + toString(argument) + " is too large for function 'tanh'";
            return 0;
        }
    }
    if(function == "truncate") {
        return trunc(argument);
    }

    error = "Unknown unary function '" + function + "'";
    return 0;
}

double evalBinaryFunction(const std::string &function, double left, double right, std::string &error) {
    if(function == "atan2") {
        try {
            return atan2(left, right);
        } catch(std::exception &e) {
            error = "Values " + toString(left) + " and " + toString(right) + " cannot be zero for function 'tanh'";
            return 0;
        }
    }
    if(function == "bigmul") {
        if(!isInteger(left) || !isInteger(right)) {
            error = "Cannot apply 'bigmul' function on floating point numbers " + toString(left) + " and " + toString(right);
            return 0;
        }

        return left * right;
    }
    if(function == "ieeeremainder") {
        if(right == 0) {
            error = "Value " + toString(right) + " cannot be zero for function 'ieeeremainder'";
            return 0;
        }

        return left - round(left / right) * right;
    }
    if(function == "log") {
        if(right == 0 && left == 1)
            return 0;
        if(right <= 0) {
            error = "Cannot apply 'log' binary function on zero or negative base " + toString(right);
            return 0;
        }
        if(left <= 0) {
            error = "Value " + toString(left) + " out of range for function 'log'";
            return 0;
        }

        return log(left) / log(right);
    }
    if(function == "max") {
        return left >= right ? left : right;
    }
    if(function == "min") {
        return left <= right ? left : right;
    }
    if(function == "pow") {
        if(left < 0 && !isInteger(right)) {
            error = "Value " + toString(right) + " out of range for function 'pow'";
            return 0;
        }
        if(left == 0 && right == 0) {
            error = "Values " + toString(left) + " and " + toString(right) + " cannot be zero for function 'pow'";
            return 0;
        }
        if(left == 0 && right < 0) {
            error = "Cannot apply 'pow' function on zero base " + toString(left) + " and negative exponent " + toString(right);
            return 0;
        }

        try {
            return pow(left, right);
        } catch(std::exception &e) {
            error = "Values " + toString(left) + " and " + toString(right) + " are too large or too small for function 'pow'";
            return 0;
        }
    }

    error = "Unknown binary function '" + function + "'";
    return 0;
}

double evalExpressionTree(BinaryTree* tree, std::string &error) {
    if(tree == nullptr || !error.empty())
        return 0;

    if(tree->left == nullptr && tree->right == nullptr) {
        if(!isOperand(tree->data)) {
            error = "Expected arguments for operator or function '" + tree->data + "'";
            return 0;
        }
        return stod(tree->data);
    }

    if(isBinaryOperator(tree->data)) {
        if((tree->left == nullptr || tree->right == nullptr) && !isUnaryOperator(tree->data)) {
            error = "Expected two arguments for binary operator '" + tree->data + "'";
            return 0;
        }
        if(tree->right != nullptr)
            return evalBinaryOperator(tree->data, evalExpressionTree(tree->left, error), evalExpressionTree(tree->right, error), error);
    }
    if(isUnaryOperator(tree->data)) {
        if(tree->left == nullptr) {
            error = "Expected argument for unary operator '" + tree->data + "'";
            return 0;
        }
        if(tree->right != nullptr) {
            error = "Unexpected second argument " + tree->right->data + " for unary operator '" + tree->data + "'";
            return 0;
        }
        return evalUnaryOperator(tree->data, evalExpressionTree(tree->left, error), error);
    }
    if(isBinaryFunction(tree->data)) {
        if((tree->left == nullptr || tree->right == nullptr) && !isUnaryFunction(tree->data)) {
            error = "Expected two arguments for binary function '" + tree->data + "'";
            return 0;
        }
        if(tree->right != nullptr)
            return evalBinaryFunction(tree->data, evalExpressionTree(tree->left, error), evalExpressionTree(tree->right, error), error);
    }
    if(isUnaryFunction(tree->data)) {
        if(tree->left == nullptr) {
            error = "Expected argument for unary function '" + tree->data + "'";
            return 0;
        }
        if(tree->right != nullptr) {
            error = "Unexpected second argument " + tree->right->data + " for unary function '" + tree->data + "'";
            return 0;
        }
        return evalUnaryFunction(tree->data, evalExpressionTree(tree->left, error), error);
    }

    error = "Unexpected arguments for operand '" + tree->data + "'";
    return 0;
}

Queue toPostfix(const char* infix, std::string &error, unsigned int &errorIndex) {
    Queue queue;
    Stack stack;
    // TODO: Fix variable naming.
    bool previousIsOperand = false;
    uint32_t length = strlen(infix);

    for(uint32_t i = 0; i < length; ++i) {
        char current = infix[i];

        if(isSpace(current))
            continue;

        if(isDigit(current)) {
            if(previousIsOperand) {
                Queue emptyQueue;
                error = "Expected operator (found operand)";
                errorIndex = i;

                return emptyQueue;
            }

            const char* start = infix + i;
            uint32_t count = 1;
            bool decimalSeparatorAppeared = false;

            while(i + 1 < length && (isDigit(infix[i + 1]) ||
                                     isDecimalSeparator(infix[i + 1]))) {

                if(isDecimalSeparator(infix[i + 1])) {
                    if(decimalSeparatorAppeared) {
                        Queue emptyQueue;
                        error = "Unexpected decimal separator";
                        errorIndex = i - count + 1;

                        return emptyQueue;
                    } else decimalSeparatorAppeared = true;
                }
                ++count;
                ++i;
            }

            std::string num(start, start + count);
            queue.push(num);

            previousIsOperand = true;
            continue;
        }

        if(isAlpha(current)) {
            const char* start = infix + i;
            uint32_t count = 1;

            while(i + 1 < length && (isAlpha(infix[i + 1])  ||
                                     isDigit(infix[i + 1]))) {
                ++count;
                ++i;
            }

            if(i + 1 < length && isLeftSeparator(infix[i + 1])) {
                // Function.

                std::string token(start, start + count);

                if(!isFunction(token)) {
                    Queue emptyQueue;
                    error = "Unknown function '" + token + "'";
                    errorIndex = i - count + 1;

                    return emptyQueue;
                }

                ++i;
                start = infix + i + 1;
                count = 0;

                uint16_t openSeparatorCount = 1;

                while(i + 1 < length) {
                    if(isLeftSeparator(infix[i + 1]))
                        ++openSeparatorCount;
                    else if(isRightSeparator(infix[i + 1])) {
                        --openSeparatorCount;
                        if (openSeparatorCount == 0)
                            break;
                    }

                    if(isArgumentSeparator(infix[i + 1]) && openSeparatorCount == 1)
                        break;

                    ++i;
                    ++count;
                }

                if(i + 1 >= length) {
                    Queue emptyQueue;
                    error = "Expected end of function argument";
                    errorIndex = i;

                    return emptyQueue;
                }

                if(isArgumentSeparator(infix[i + 1]) && openSeparatorCount > 1) {
                    Queue emptyQueue;
                    error = "Expected right separator at end of function argument (did you miss a ')' ?)";
                    errorIndex = i + 1;

                    return emptyQueue;
                }

                if(!isUnaryFunction(token)) {
                    if (!isArgumentSeparator(infix[i + 1])) {
                        Queue emptyQueue;
                        error = "Expected two function arguments";
                        errorIndex = i + 1;

                        return emptyQueue;
                    }
                }

                if(!isBinaryFunction(token)) {
                    if (isArgumentSeparator(infix[i + 1])) {
                        Queue emptyQueue;
                        error = "Expected only one function argument";
                        errorIndex = i + 1;

                        return emptyQueue;
                    }
                }

                std::string argExpression(start, start + count);

                if(isNullOrWhitespace(argExpression)) {
                    Queue emptyQueue;
                    error = "Unexpected empty function argument";
                    errorIndex = i - count + 1;

                    return emptyQueue;
                }

                Queue argPostfix = toPostfix(argExpression.c_str(), error, errorIndex);

                while(!argPostfix.empty()) {
                    queue.push(argPostfix.front());
                    argPostfix.pop();
                }

                if(isArgumentSeparator(infix[i + 1])) {
                    if(isUnaryFunction(token) && isBinaryFunction(token))
                        token += "_b";

                    ++i;
                    start = infix + i + 1;
                    count = 0;

                    openSeparatorCount = 1;

                    while(i + 1 < length) {
                        if(isLeftSeparator(infix[i + 1]))
                            ++openSeparatorCount;
                        else if(isRightSeparator(infix[i + 1])) {
                            --openSeparatorCount;
                            if (openSeparatorCount == 0)
                                break;
                        }

                        ++i;
                        ++count;
                    }

                    if(i + 1 >= length) {
                        Queue emptyQueue;
                        error = "Expected end of function argument";
                        errorIndex = i;

                        return emptyQueue;
                    }

                    argExpression.assign(start, count);

                    if(isNullOrWhitespace(argExpression)) {
                        Queue emptyQueue;
                        error = "Unexpected empty function argument";
                        errorIndex = i - count + 1;

                        return emptyQueue;
                    }

                    argPostfix = toPostfix(argExpression.c_str(), error, errorIndex);

                    if(argPostfix.empty()) {
                        error = "Expected non-empty argument";
                        errorIndex = i - count + 1;

                        return argPostfix;
                    }

                    while(!argPostfix.empty()) {
                        queue.push(argPostfix.front());
                        argPostfix.pop();
                    }
                } else {
                    if(isUnaryFunction(token) && isBinaryFunction(token))
                        token += "_u";
                }

                queue.push(token); // Push the function itself.
                previousIsOperand = true;
                ++i;
            } else {
                std::string token(start, start + count);

                if(isOperator(token)) {
                    // Operator.

                    if(!previousIsOperand) {
                        if(token == "+") {
                            continue;
                        } else if(token == "-") {
                            token = "neg";
                        } else {
                            Queue emptyQueue;
                            error = "Expected operand after operator";
                            errorIndex = i - count + 1;

                            return emptyQueue;
                        }
                    }

                    uint8_t precedence = getPrecedence(token);
                    while(!stack.empty() &&
                          !isLeftSeparator(stack.top().at(0)) &&
                          getPrecedence(stack.top()) <= precedence) {

                        queue.push(stack.top());
                        stack.pop();
                    }

                    stack.push(token);

                    previousIsOperand = false;
                } else {
                    // Variable.

                    if(previousIsOperand) {
                        Queue emptyQueue;
                        error = "Expected operand after operator";
                        errorIndex = i - count + 1;

                        return emptyQueue;
                    }

                    queue.push(token);
                    previousIsOperand = true;
                }
            }
            continue;
        }

        if(isLeftSeparator(current)) {
            if(previousIsOperand) {
                Queue emptyQueue;
                error = "Expected operator before index (found operand)";
                errorIndex = i;

                return emptyQueue;
            }

            stack.push(toString(current));
            continue;
        }

        if(isRightSeparator(current)) {
            while(!stack.empty() &&
                  !isLeftSeparator(stack.top().at(0))) {

                queue.push(stack.top());
                stack.pop();
            }

            if(!stack.empty() &&
               isLeftSeparator(stack.top().at(0)))
                stack.pop();

            previousIsOperand = true;
            continue;
        }

        // Operator.

        const char* start = infix + i;
        uint32_t count = 1;

        while(i + 1 < length && !isDigit(infix[i + 1]) &&
                                !isAlpha(infix[i + 1]) &&
                                !isSpace(infix[i + 1]) &&
                                !isSeparator(infix[i + 1])) {
            ++count;
            ++i;
        }

        std::string token(start, start + count);

        if(isOperator(token)) {
            if(!previousIsOperand) {
                if(token == "+") {
                    continue;
                } else if(token == "-") {
                    token = "neg";
                } else {
                    Queue emptyQueue;
                    error = "Expected operand after operator";
                    errorIndex = i - count + 1;

                    return emptyQueue;
                }
            }

            uint8_t precedence = getPrecedence(token);
            while(!stack.empty() &&
                  !isLeftSeparator(stack.top().at(0)) &&
                  getPrecedence(stack.top()) <= precedence) {

                queue.push(stack.top());
                stack.pop();
            }

            stack.push(token);

            previousIsOperand = false;
        } else {
            Queue emptyQueue;
            error = "Unknown operator '" + token + "'";
            errorIndex = i - count + 1;

            return emptyQueue;
        }
    }

    if(!previousIsOperand) {
        Queue emptyQueue;
        error = "Expected operand after operator";
        errorIndex = length - 1;

        return emptyQueue;
    }

    while(!stack.empty()) {
        queue.push(stack.top());
        stack.pop();
    }

    return queue;
}

Queue substitute(Queue expression, const std::string* variables, const double* values, uint32_t count) {
    Queue sub;

    std::string stringValues[count];

    for(uint32_t i = 0; i < count; ++i)
        stringValues[i] = toString(values[i] > 0 ? values[i] : -1 * values[i]);

    while(!expression.empty()) {
        std::string token = expression.front();

        uint32_t i;
        for(i = 0; i < count; ++i) {
            if(token == variables[i]) {
                sub.push(stringValues[i]);
                if(values[i] < 0)
                    sub.push("neg");
                break;
            }
        }

        if(i == count)
            sub.push(token);

        expression.pop();
    }

    return sub;
}

char* substitute(const char* expression, const std::string* variables, const double* values, const uint32_t count) {
    std::string sub(expression);

    sub.reserve(sub.size() > 128 ? 2 * sub.size() : 256); // To minimize the amount of re-allocations.

    for(uint32_t i = 0; i < count; ++i) {
        std::string value = toString(values[i]);
        size_t pos = sub.find(variables[i]);

        while (pos != std::string::npos) {
            sub.replace(pos, (variables[i]).size(), value);
            pos = sub.find(variables[i], pos + value.size());
        }
    }

    sub.reserve(sub.size()); // Bring back the capacity to the actual size.

    char* c = (char*) malloc((sub.size() + 1) * sizeof(char));
    strcpy(c, sub.c_str());
    return c;
}

char* serializePostfix(Queue postfix) {
    postfix = postfix.copy();

    if(postfix.empty())
        return nullptr;

    std::string serialized;
    serialized.reserve(postfix.size * 3); // To minimize the amount of re-allocations.

    serialized += postfix.front();
    postfix.pop();

    while(!postfix.empty()) {
        serialized += " " + postfix.front();
        postfix.pop();
    }

    serialized.reserve(serialized.size()); // Bring back the capacity to the actual size.

    char* c = (char*) malloc((serialized.size() + 1) * sizeof(char));
    strcpy(c, serialized.c_str());
    return c;
}

Queue deserializePostfix(const char* infix) {
    Queue deserialized;

    char *tokens = (char*) malloc((strlen(infix) + 1) * sizeof(char));
    strcpy(tokens, infix);
    char *token = strtok(tokens, " ");

    while(token != nullptr) {
        deserialized.push(token);
        token = strtok(nullptr, " ");
    }

    return deserialized;
}