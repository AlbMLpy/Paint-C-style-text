#include "Painter.h"
#include <cstdio>

/**
 * This function is used to print token of Token type in different fixed set of colors;
 * Parameters:
 *     - "token" is a reference on Token object;
 *     - "paint" is a pointer on color in set below;
 */ 
void
Painter::print_colored(Token &token, const char *paint) const
{
    static const char *no_paint_code = "\033[0m"; // cancel paint
    printf("%s", paint);
    token.print();
    printf("%s", no_paint_code);
}    

int
Painter::action(Token &token) 
{
    static const char *blue_code = "\033[0;34m"; // key words
    static const char *pink_code = "\033[0;35m"; // identificators
    static const char *orange_code = "\033[0;33m"; // const int
    static const char *yellow_code = "\033[1;33m"; // const char
    static const char *green_code = "\033[0;32m"; // const string
    static const char *red_code = "\033[0;31m"; // punctuators
    static const char *brown_code = "\033[0;33m"; // comments
    
    switch (token.get_type()) {
    case IDENT:
        print_colored(token, pink_code);
        break;
   
    case KEY:
        print_colored(token, blue_code);
        break;  
    
    case CONST_INT:
        print_colored(token, orange_code);
        break;

    case CONST_CHAR:
        print_colored(token, yellow_code);
        break;

    case CONST_STR:
        print_colored(token, green_code);
        break;

    case COMMENT:
        print_colored(token, brown_code);
        break;

    case PUNCT:
        print_colored(token, red_code);
        break;

    default:
        token.print();
    }
    return 0;
}

Painter::~Painter(){}
Painter::Painter(){}
