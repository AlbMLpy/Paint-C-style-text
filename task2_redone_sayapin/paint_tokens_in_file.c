#include "paint_tokens_in_file.h"
#include "painter_container.h"

int
paint(Painter *does, struct Dynamic_Vec_Token *vec)
{
    does->print_token_in_color(vec);
    return 0;
}    

void
print_token_in_color(struct Dynamic_Vec_Token *vec)
{
    static char *blue_code = "\033[0;34m"; // key words
    static char *pink_code = "\033[0;35m"; // identificators
    static char *orange_code = "\033[0;33m"; // const int
    static char *yellow_code = "\033[1;33m"; // const char
    static char *green_code = "\033[0;32m"; // const string
    static char *red_code = "\033[0;31m"; // punctuators
    static char *brown_code = "\033[0;33m"; // comments
    
    switch (get_type_token(vec)) {
    case IDENT:
        print_cont_in_color(vec, print_token, pink_code);
        break;
   
    case KEY:
        print_cont_in_color(vec, print_token, blue_code);
        break;  
    
    case CONST_INT:
        print_cont_in_color(vec, print_token, orange_code);
        break;

    case CONST_CHAR:
        print_cont_in_color(vec, print_token, yellow_code);
        break;

    case CONST_STR:
        print_cont_in_color(vec, print_token, green_code);
        break;

    case COMMENT:
        print_cont_in_color(vec, print_token, brown_code);
        break;

    case PUNCT:
        print_cont_in_color(vec, print_token, red_code);
        break;

    default:
        print_token(vec);
    }
}   

