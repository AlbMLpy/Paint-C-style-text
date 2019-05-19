#ifndef PAINT_STRING
#define PAINT_STRING

#include <string>

enum Color {BLUE, PINK, ORANGE, YELLOW, GREEN, RED, BROWN, NOCOLOR};

using std::string;
/**
 * This function is used to paint C++ string into colors above;
 * Input parameters:
 * - "str" is a string with contant to be painter;
 * - "paint" is a color used for painting a string;
 * Returns object of string type;
 */ 
string paint_string(const string &str, Color paint);

#endif
