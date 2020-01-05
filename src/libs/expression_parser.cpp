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

BinaryTree* toExpressionTree(Queue postfix) {
    TreeStack stack;
    postfix = postfix.copy();

    while(!postfix.empty()) {
        std::string token = postfix.front();
        postfix.pop();

        if(isOperator(token)) {
            BinaryTree* tree = new BinaryTree;

            if(isUnaryOperator(token)) {
                if(token == "neg") {
                    tree->data = "-";
                } else tree->data = token;

                tree->right = stack.top();
                stack.pop();
                tree->left = nullptr;

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
                tree->right = stack.top();
                stack.pop();
                tree->left = nullptr;

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
                tree->right = stack.top();
                stack.pop();
                tree->left = nullptr;

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

Queue toPostfix(const char* infix, std::string &error, unsigned int &errorIndex) {
    Queue queue;
    Stack stack;

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

            while(i + 1 < length && isAlpha(infix[i + 1])) {
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
        stringValues[i] = std::to_string(values[i] > 0 ? values[i] : -1 * values[i]);

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
        std::string value = std::to_string(values[i]);
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

double evalPostfix(Queue postfix) {
    Stack stack;

    while(!postfix.empty()) {
        std::string token = postfix.front();
        postfix.pop();

        if(isOperator(token)) {
            if(token == "+") {
                double op2 = stod(stack.top());
                stack.pop();
                double op1 = stod(stack.top());
                stack.pop();

                std::string result(std::to_string(op1 + op2));
                stack.push(result);
            } else if(token == "-") {
                double op2 = stod(stack.top());
                stack.pop();
                double op1 = stod(stack.top());
                stack.pop();

                std::string result(std::to_string(op1 - op2));
                stack.push(result);
            } else if(token == "*") {
                double op2 = stod(stack.top());
                stack.pop();
                double op1 = stod(stack.top());
                stack.pop();

                std::string result(std::to_string(op1 * op2));
                stack.push(result);
            } else if(token == "/") {
                double op2 = stod(stack.top());
                stack.pop();
                double op1 = stod(stack.top());
                stack.pop();

                std::string result(std::to_string(op1 / op2));
                stack.push(result);
            } else if(token == "%") {
                double op2 = stod(stack.top());
                stack.pop();
                double op1 = stod(stack.top());
                stack.pop();

                std::string result(std::to_string((int) op1 % (int) op2));
                stack.push(result);
            } else if(token == "neg") {
                double op = stod(stack.top());
                stack.pop();

                std::string result(std::to_string((-1) * op));
                stack.push(result);
            }
        } else if(isFunction(token) || (token.size() > 2 && isFunction(token.substr(0, token.size() - 2)))) {
            if(token == "pow") {
                double op2 = stod(stack.top());
                stack.pop();
                double op1 = stod(stack.top());
                stack.pop();

                std::string result(std::to_string(pow(op1, op2)));
                stack.push(result);
            } else if(token == "log_u") {
                double op = stod(stack.top());
                stack.pop();

                std::string result(std::to_string(log(op)));
                stack.push(result);
            } else if(token == "log_b") {
                double op2 = stod(stack.top());
                stack.pop();
                double op1 = stod(stack.top());
                stack.pop();

                std::string result(std::to_string(log(op1) / log(op2)));
                stack.push(result);
            }
        } else {
            char *tmp;
            double value = strtod(token.c_str(), &tmp);

            // Not a number.
            if(*tmp)
                stack.push("0"); // The default value of variables.
            else stack.push(token);
        }
    }

    return stod(stack.top());
}

double evalPostfix(const char* postfix) {
    Stack stack;

    char *tokens = (char*) malloc((strlen(postfix) + 1) * sizeof(char));
    strcpy(tokens, postfix);
    char *token = strtok(tokens, " ");

    while(token != nullptr) {
        if(strlen(token) == 1 && isOperator(token)) {
            switch(token[0]) {
                case '+': {
                    double op1 = stod(stack.top());
                    stack.pop();
                    double op2 = stod(stack.top());
                    stack.pop();

                    std::string result(std::to_string(op2 + op1));
                    stack.push(result);
                    break;
                } case '-': {
                    double op1 = stod(stack.top());
                    stack.pop();
                    double op2 = stod(stack.top());
                    stack.pop();

                    std::string result(std::to_string(op2 - op1));
                    stack.push(result);
                    break;
                } case '*': {
                    double op1 = stod(stack.top());
                    stack.pop();
                    double op2 = stod(stack.top());
                    stack.pop();

                    std::string result(std::to_string(op2 * op1));
                    stack.push(result);
                    break;
                } case '/': {
                    double op1 = stod(stack.top());
                    stack.pop();
                    double op2 = stod(stack.top());
                    stack.pop();

                    std::string result(std::to_string(op2 / op1));
                    stack.push(result);
                    break;
                } case '%': {
                    double op1 = stod(stack.top());
                    stack.pop();
                    double op2 = stod(stack.top());
                    stack.pop();

                    std::string result(std::to_string((int32_t) op2 % (int32_t) op1));
                    stack.push(result);
                    break;
                } case '^': {
                    double op1 = stod(stack.top());
                    stack.pop();
                    double op2 = stod(stack.top());
                    stack.pop();

                    std::string result(std::to_string(pow(op2, op1)));
                    stack.push(result);
                    break;
                } case 'n': {
                    double op1 = stod(stack.top());
                    stack.pop();

                    std::string result(std::to_string((-1) * op1));
                    stack.push(result);
                    break;
                }
            }
        } else {
            char *tmp;
            double value = strtod(token, &tmp);

            // Not a number.
            if(*tmp)
                stack.push("0"); // The default value of variables.
            else stack.push(token);
        }

        token = strtok(nullptr, " ");
    }

    return stod(stack.top());
}

double evalPostfix(Queue postfix, const std::string* variables, const double* values, const uint32_t count) {
    Stack stack;

    while(!postfix.empty()) {
        std::string token = postfix.front();
        postfix.pop();

        if(token.length() == 1 && isOperator(token)) {
            switch(token.at(0)) {
                case '+': {
                    double op1 = stod(stack.top());
                    stack.pop();
                    double op2 = stod(stack.top());
                    stack.pop();

                    std::string result(std::to_string(op2 + op1));
                    stack.push(result);
                    break;
                } case '-': {
                    double op1 = stod(stack.top());
                    stack.pop();
                    double op2 = stod(stack.top());
                    stack.pop();

                    std::string result(std::to_string(op2 - op1));
                    stack.push(result);
                    break;
                } case '*': {
                    double op1 = stod(stack.top());
                    stack.pop();
                    double op2 = stod(stack.top());
                    stack.pop();

                    std::string result(std::to_string(op2 * op1));
                    stack.push(result);
                    break;
                } case '/': {
                    double op1 = stod(stack.top());
                    stack.pop();
                    double op2 = stod(stack.top());
                    stack.pop();

                    std::string result(std::to_string(op2 / op1));
                    stack.push(result);
                    break;
                } case '%': {
                    double op1 = stod(stack.top());
                    stack.pop();
                    double op2 = stod(stack.top());
                    stack.pop();

                    std::string result(std::to_string((int32_t) op2 % (int32_t) op1));
                    stack.push(result);
                    break;
                } case '^': {
                    double op1 = stod(stack.top());
                    stack.pop();
                    double op2 = stod(stack.top());
                    stack.pop();

                    std::string result(std::to_string(pow(op2, op1)));
                    stack.push(result);
                    break;
                } case 'n': {
                    double op1 = stod(stack.top());
                    stack.pop();

                    std::string result(std::to_string((-1) * op1));
                    stack.push(result);
                    break;
                }
            }
        } else {
            char *tmp;
            double value = strtod(token.c_str(), &tmp);

            // Not a number.
            if(*tmp) {
                uint32_t i;

                for(i = 0; i < count; ++i) {
                    if(variables[i] == token) {
                        stack.push(std::to_string(values[i]));
                        break;
                    }
                }

                if(i == count)
                    stack.push(std::to_string(0)); // The default value of variables.
            }
            else stack.push(token);
        }
    }

    return stod(stack.top());
}

double evalPostfix(const char* postfix, const std::string* variables, const double* values, const uint32_t count) {
    Stack stack;

    char *tokens = (char*) malloc((strlen(postfix) + 1) * sizeof(char));
    strcpy(tokens, postfix);
    char *token = strtok(tokens, " ");

    while(token != nullptr) {
        if(strlen(token) == 1 && isOperator(token)) {
            switch(token[0]) {
                case '+': {
                    double op1 = stod(stack.top());
                    stack.pop();
                    double op2 = stod(stack.top());
                    stack.pop();

                    std::string result(std::to_string(op2 + op1));
                    stack.push(result);
                    break;
                } case '-': {
                    double op1 = stod(stack.top());
                    stack.pop();
                    double op2 = stod(stack.top());
                    stack.pop();

                    std::string result(std::to_string(op2 - op1));
                    stack.push(result);
                    break;
                } case '*': {
                    double op1 = stod(stack.top());
                    stack.pop();
                    double op2 = stod(stack.top());
                    stack.pop();

                    std::string result(std::to_string(op2 * op1));
                    stack.push(result);
                    break;
                } case '/': {
                    double op1 = stod(stack.top());
                    stack.pop();
                    double op2 = stod(stack.top());
                    stack.pop();

                    std::string result(std::to_string(op2 / op1));
                    stack.push(result);
                    break;
                } case '%': {
                    double op1 = stod(stack.top());
                    stack.pop();
                    double op2 = stod(stack.top());
                    stack.pop();

                    std::string result(std::to_string((int32_t) op2 % (int32_t) op1));
                    stack.push(result);
                    break;
                } case '^': {
                    double op1 = stod(stack.top());
                    stack.pop();
                    double op2 = stod(stack.top());
                    stack.pop();

                    std::string result(std::to_string(pow(op2, op1)));
                    stack.push(result);
                    break;
                } case 'n': {
                    double op1 = stod(stack.top());
                    stack.pop();

                    std::string result(std::to_string((-1) * op1));
                    stack.push(result);
                    break;
                }
            }
        } else {
            char *tmp;
            double value = strtod(token, &tmp);

            // Not a number.
            if(*tmp) {
                uint32_t i;

                for(i = 0; i < count; ++i) {
                    if(variables[i] == token) {
                        stack.push(std::to_string(values[i]));
                        break;
                    }
                }

                if(i == count)
                    stack.push(std::to_string(0)); // The default value of variables.
            }
            else stack.push(token);
        }

        token = strtok(nullptr, " ");
    }

    return stod(stack.top());
}

double evalInfix(const char* infix) {
    std::string error;
    uint32_t errorIndex;
    return evalPostfix(toPostfix(infix, error, errorIndex));
}

double evalInfix(const char* infix, const std::string* variables, const double* values, const uint32_t count) {
    std::string error;
    uint32_t errorIndex;
    return evalPostfix(toPostfix(infix, error, errorIndex), variables, values, count);
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