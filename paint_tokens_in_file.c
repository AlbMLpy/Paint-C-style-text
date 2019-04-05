#include "paint_tokens_in_file.h"
//#include "dyn_vec_token.h"
#include "painter_container.h"
#include "define_token.h"
#include <stdio.h>

/**
 * Input parameters:
 *    - "vec" is a pointer on previously initializer object of type below;
 *    - "paint" is a variable depending on type of token;
 * Description:
 *    This function prints token in appropriate color to standart output;
 */
static void
print_token_in_color(struct Dynamic_Vec_Token *vec, char paint);

void
print_colored_tokens(FILE *fd)
{
    struct Dynamic_Vec_Token *vec = initialize_vec_token();
    if (vec == NULL) {
        fprintf(stderr, "%s\n", "Memory error!");
        return;
    }
    if (give_token(vec, fd) == NULL) {
        fprintf(stderr, "%s\n", "Memory error!");
        return;
    }
    char type_token = get_type_token(vec);
    while (type_token != EOF_RET) {
        print_token_in_color(vec, type_token);
        set_end_token(vec, 0);
        if (give_token(vec, fd) == NULL) {
            fprintf(stderr, "%s\n", "Memory error!");
            return;
        }
        type_token = get_type_token(vec);
    }
    finalize_vec_token(vec);
    return;
}    


static void
print_token_in_color(struct Dynamic_Vec_Token *vec, char paint)
{
    static char *blue_code = "\033[0;34m"; // key words
    static char *pink_code = "\033[0;35m"; // identificators
    static char *orange_code = "\033[0;33m"; // const int
    static char *yellow_code = "\033[1;33m"; // const char
    static char *green_code = "\033[0;32m"; // const string
    static char *red_code = "\033[0;31m"; // punctuators
    static char *brown_code = "\033[0;33m"; // comments
    
    switch (paint) {
    case IDENT:
        print_cont_in_color((void*)vec, (void*)print_token, pink_code);
        break;
   
    case KEY:
        print_cont_in_color((void*)vec, (void*)print_token, blue_code);
        break;  
    
    case CONST_INT:
        print_cont_in_color((void*)vec, (void*)print_token, orange_code);
        break;

    case CONST_CHAR:
        print_cont_in_color((void*)vec, (void*)print_token, yellow_code);
        break;

    case CONST_STR:
        print_cont_in_color((void*)vec, (void*)print_token, green_code);
        break;

    case COMMENT:
        print_cont_in_color((void*)vec, (void*)print_token, brown_code);
        break;

    case PUNCT:
        print_cont_in_color((void*)vec, (void*)print_token, red_code);
        break;

    default:
        print_token(vec);
    }
}   

