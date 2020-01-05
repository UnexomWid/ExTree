#include "charlib.h"

std::string toString(const char token) {
    std::string string(1, token);
    return string;
}

std::string toLower(const std::string &token) {
    std::string lower;
    lower.reserve(token.length());

    for(char i : token)
        lower += i;
    return lower;
}

bool isSpace(const char token) {
    return token == ' ';
}

bool isDigit(const char token) {
    return (token >= '0' && token <= '9');
}

bool isAlpha(const char token) {
    return (token >= 'a' && token <= 'z') || (token >= 'A' && token <= 'Z');
}

bool isLeftSeparator(const char token) {
    return token == '(';
}

bool isRightSeparator(const char token) {
    return token == ')';
}

bool isSeparator(char token) {
    return isLeftSeparator(token) || isRightSeparator(token);
}

bool isDecimalSeparator(const char token) {
    return token == '.';
}

bool isArgumentSeparator(const char token) {
    return token == ',';
}

bool isNumber(const std::string &token) {
    for(char c : token)
        if(!isDigit(c) && !isArgumentSeparator(c))
            return false;
    return true;
}

bool isNullOrWhitespace(const std::string &token) {
    if(token.empty())
        return true;

    for(char i : token)
        if(i != ' ' && i != '\0' && i != '\t')
            return false;

    return true;
}