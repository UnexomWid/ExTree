#ifndef CHARLIB_H_INCLUDED
#define CHARLIB_H_INCLUDED

#include <string>

std::string toString(char token);

std::string toLower(const std::string &token);

bool isSpace(char token);

bool isDigit(char token);

bool isAlpha(char token);

bool isLeftSeparator(char token);

bool isRightSeparator(char token);

bool isSeparator(char token);

bool isDecimalSeparator(char token);

bool isArgumentSeparator(char token);

bool isNullOrWhitespace(const std::string &token);

bool isNumber(const std::string &token);

#endif // CHARLIB_H_INCLUDED
