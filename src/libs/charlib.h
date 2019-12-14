#ifndef CHARLIB_H
#define CHARLIB_H

#include <string>

std::string toLower(const std::string &token);

bool isSpace(const char token);

bool isDigit(const char token);

bool isAlpha(const char token);

bool isLeftSeparator(const char token);

bool isRightSeparator(const char token);

bool isSeparator(char token);

bool isDecimalSeparator(const char token);

std::string toString(const char token);

#endif // CHARLIB_H
