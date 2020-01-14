#include "charlib.h"

std::string toString(const char token) {
    std::string string(1, token);
    return string;
}

std::string toString(double token) {
    char* buffer = (char*) malloc(256 * sizeof(char));
    sprintf(buffer, DOUBLE_NUMBERS_FORMAT, token);

    std::string string(buffer);
    free(buffer);

    return string;
}

std::string toLower(const std::string &token) {
    std::string lower;
    lower.reserve(token.length());

    for(uint i = 0; i < token.size(); ++i)
        lower += token.at(i);
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
    for(uint i = 0; i < token.size(); ++i)
        if(!isDigit(token.at(i)) && !isArgumentSeparator(token.at(i)) && token.at(i) != '-')
            return false;
    return true;
}

bool isNullOrWhitespace(const std::string &token) {
    if(token.empty())
        return true;

    for(uint i = 0; i < token.size(); ++i)
        if(token.at(i) != ' ' && token.at(i) != '\0' && token.at(i) != '\t')
            return false;

    return true;
}
