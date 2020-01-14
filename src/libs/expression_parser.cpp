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
    return isNumber(token)   ||
         (!isOperator(token) &&
          !isFunction(token) &&
          !isNullOrWhitespace(token));
}

bool isVariable(const std::string &token) {
    return isOperand(token) &&
           !isNumber(token) &&
           !isConstant(token);
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

bool isInteger(double value) {
    return floor(value) == value;
}

ushort getOperatorPrecedence(const std::string &token) {
    std::string lowerToken = toLower(token);

    if(lowerToken == "neg")
        return 1;

    if(lowerToken == "*" ||
       lowerToken == "/" )
        return 2;

    if(lowerToken == "\\")
        return 3;

    if(lowerToken == "+" ||
       lowerToken == "-" )
        return 4;

    if(lowerToken == "mod")
        return 5;

    if(lowerToken == "="  ||
       lowerToken == "<>" ||
       lowerToken == "<"  ||
       lowerToken == "<=" ||
       lowerToken == ">"  ||
       lowerToken == ">=" )
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

double getConstantValue(const std::string &token) {
    std::string lowerToken = toLower(token);

    if(token == "true")
        return TRUE;
    if(token == "false")
        return FALSE;
    if(token == "pi")
        return PI;
    if(token == "e")
        return E;
    return 0;
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
        if(argument == E)
            return 1;
        if(argument == 1)
            return 0;
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
        if(right == 1 && left != 1) {
            error = "Cannot apply 'log' binary function on base " + toString(right) + " and value " + toString(left);
            return 0;
        }

        if(left == 1)
            return 0;
        if(left == right)
            return 1;
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

Queue toPostfix(const char* infix, std::string &error, uint &errorIndex) {
    Queue queue;
    Stack stack;

    bool previousIsOperand = false;
    bool previousIsOperator = false;

    uint length = strlen(infix);

    for(uint i = 0; i < length; ++i) {
        char current = infix[i];

        if(isSpace(current))
            continue;

        if(isDigit(current)) {
            if(previousIsOperand) {
                error = "Expected operator (found operand)";
                errorIndex = i;

                RETURN_EMPTY_QUEUE
            }

            const char* start = infix + i;
            uint count = 1;
            bool decimalSeparatorAppeared = false;

            while(i + 1 < length && (isDigit(infix[i + 1]) ||
                                     isDecimalSeparator(infix[i + 1]))) {

                if(isDecimalSeparator(infix[i + 1])) {
                    if(decimalSeparatorAppeared) {
                        error = "Unexpected decimal separator";
                        errorIndex = i - count + 1;

                        RETURN_EMPTY_QUEUE
                    } else decimalSeparatorAppeared = true;
                }
                ++count;
                ++i;
            }

            std::string num(start, start + count);
            queue.push(num);

            previousIsOperand = true;
            previousIsOperator = false;
            continue;
        }

        if(isAlpha(current)) {
            const char* start = infix + i;
            uint count = 1;

            while(i + 1 < length && (isAlpha(infix[i + 1])  ||
                                     isDigit(infix[i + 1]))) {
                ++count;
                ++i;
            }

            if(i + 1 < length && isLeftSeparator(infix[i + 1])) {
                // --------------------------------------------------
                // Function.
                // --------------------------------------------------

                std::string token(start, start + count);

                if(!isFunction(token)) {
                    error = "Unknown function '" + token + "'";
                    errorIndex = i - count + 1;

                    RETURN_EMPTY_QUEUE
                }

                ++i;
                start = infix + i + 1;
                count = 0;

                ushort openSeparatorCount = 1;

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
                    error = "Expected end of function argument";
                    errorIndex = i;

                    RETURN_EMPTY_QUEUE
                }

                if(isArgumentSeparator(infix[i + 1]) && openSeparatorCount > 1) {
                    error = "Expected right separator at end of function argument (did you miss a ')' ?)";
                    errorIndex = i + 1;

                    RETURN_EMPTY_QUEUE
                }

                if(!isUnaryFunction(token)) {
                    if (!isArgumentSeparator(infix[i + 1])) {
                        error = "Expected two function arguments";
                        errorIndex = i + 1;

                        RETURN_EMPTY_QUEUE
                    }
                }

                if(!isBinaryFunction(token)) {
                    if (isArgumentSeparator(infix[i + 1])) {
                        error = "Expected only one function argument";
                        errorIndex = i + 1;

                        RETURN_EMPTY_QUEUE
                    }
                }

                std::string argExpression(start, start + count);

                if(isNullOrWhitespace(argExpression)) {
                    error = "Unexpected empty function argument";
                    errorIndex = i - count + 1;

                    RETURN_EMPTY_QUEUE
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
                        error = "Expected end of function argument";
                        errorIndex = i;

                        RETURN_EMPTY_QUEUE
                    }

                    argExpression.assign(start, count);

                    if(isNullOrWhitespace(argExpression)) {
                        error = "Unexpected empty function argument";
                        errorIndex = i - count + 1;

                        RETURN_EMPTY_QUEUE
                    }

                    argPostfix = toPostfix(argExpression.c_str(), error, errorIndex);

                    if(argPostfix.empty()) {
                        error = "Expected non-empty argument";
                        errorIndex = i - count + 1;

                        RETURN_EMPTY_QUEUE
                    }

                    while(!argPostfix.empty()) {
                        queue.push(argPostfix.front());
                        argPostfix.pop();
                    }
                } else {
                    if(isUnaryFunction(token) && isBinaryFunction(token))
                        token += "_u";
                }

                queue.push(token);

                previousIsOperand = true;
                previousIsOperator = false;

                ++i;
            } else {
                std::string token(start, start + count);

                if(isOperator(token)) {
                    // --------------------------------------------------
                    // Operator.
                    // --------------------------------------------------

                    if(!previousIsOperand) {
                        if(token == "+" && !previousIsOperator) {
                            continue;
                        } else if(token == "-" && !previousIsOperator) {
                            token = "neg";
                        } else {
                            error = "Expected operand after operator";
                            errorIndex = i - count + 1;

                            RETURN_EMPTY_QUEUE
                        }
                    }

                    uchar precedence = getOperatorPrecedence(token);
                    while(!stack.empty() &&
                          !isLeftSeparator(stack.top().at(0)) &&
                           getOperatorPrecedence(stack.top()) <= precedence) {

                        queue.push(stack.top());
                        stack.pop();
                    }

                    stack.push(token);

                    previousIsOperand = false;
                    previousIsOperator = true;
                } else {
                    // --------------------------------------------------
                    // Variable.
                    // --------------------------------------------------

                    if(previousIsOperand) {
                        error = "Expected operand after operator";
                        errorIndex = i - count + 1;

                        RETURN_EMPTY_QUEUE
                    }

                    queue.push(token);
                    previousIsOperand = true;
                    previousIsOperator = false;
                }
            }
            continue;
        }

        if(isLeftSeparator(current)) {
            if(previousIsOperand) {
                error = "Expected operator before index (found operand)";
                errorIndex = i;

                RETURN_EMPTY_QUEUE
            }

            stack.push(toString(current));
            previousIsOperator = false;
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
            previousIsOperator = false;
            continue;
        }

        // --------------------------------------------------
        // Operator.
        // --------------------------------------------------

        const char* start = infix + i;
        uint count = 1;

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
                if(token == "+" && !previousIsOperator) {
                    continue;
                } else if(token == "-" && !previousIsOperator) {
                    token = "neg";
                } else {
                    error = "Expected operand after operator";
                    errorIndex = i - count + 1;

                    RETURN_EMPTY_QUEUE
                }
            }

            uchar precedence = getOperatorPrecedence(token);
            while(!stack.empty() &&
                  !isLeftSeparator(stack.top().at(0)) &&
                   getOperatorPrecedence(stack.top()) <= precedence) {

                queue.push(stack.top());
                stack.pop();
            }

            stack.push(token);

            previousIsOperand = false;
            previousIsOperator = true;
        } else {
            error = "Unknown operator '" + token + "'";
            errorIndex = i - count + 1;

            RETURN_EMPTY_QUEUE
        }
    }

    if(!previousIsOperand) {
        error = "Expected operand after operator";
        errorIndex = length - 1;

        RETURN_EMPTY_QUEUE
    }

    while(!stack.empty()) {
        queue.push(stack.top());
        stack.pop();
    }

    return queue;
}

std::string getNextVariable(BinaryTree* tree) {
    if(tree == nullptr)
        return "";

    TreeQueue queue;

    queue.push(tree);

    while(!queue.empty()) {
        if(queue.front() != nullptr) {
            if(isVariable(queue.front()->data))
                return queue.front()->data;

            if(queue.front()->right != nullptr)
                queue.push(queue.front()->right);
            if(queue.front()->left != nullptr)
                queue.push(queue.front()->left);
        }

        queue.pop();
    }

    return "";
}

void substitute(BinaryTree* &tree, const std::string &variable, double value) {
    if(tree == nullptr)
        return;

    if(tree->data == variable)
        tree->data = toString(value);

    substitute(tree->left, variable, value);
    substitute(tree->right, variable, value);
}

void substituteConstants(BinaryTree* &tree) {
    if(tree == nullptr)
        return;

    if(isConstant(tree->data))
        tree->data = toString(getConstantValue(tree->data));

    substituteConstants(tree->left);
    substituteConstants(tree->right);
}

char* postfixToString(Queue postfix) {
    postfix = postfix.copy();

    if(postfix.empty())
        return nullptr;

    std::string string;

    // Estimate the amount of space needed.
    string.reserve(postfix.size * 3);

    string += postfix.front();
    postfix.pop();

    while(!postfix.empty()) {
        string += " " + postfix.front();
        postfix.pop();
    }

    // Bring the capacity to the actual size, in order to not waste memory.
    string.reserve(string.size());

    char* c = (char*) malloc((string.size() + 1) * sizeof(char));
    strcpy(c, string.c_str());
    return c;
}
