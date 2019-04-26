/// The entities from stdio.h are used in the next entities
#include <cstdio>
#include "Token.h"

/**
 * This class is used for work with file to define token as in standart
 * of C language.
 */ 
class Define_Token {
    FILE *fd;

    void int_dec_token(Token &token);
    void int_oct_token(Token &token);
    void char_token(Token &token);
    void string_token(Token &token);
    void ident_token(Token &token);
    void comment_new_token(Token &token);
    void comment_old_token(Token &token);
    void punct_token(Token &token);
    int equal_sets(Token &token, char *set);
    int is_key(Token &token);
    void hex_only(Token &token);
    void oct_less_eq_3(Token &token);
    void u_4_8_hex(Token &token);    
public:
    Define_Token(FILE *fp);
    ~Define_Token(); 
/**
 * Input parameters:
 *    - "token" is a reference on previously initialized object of type Token;
 * This function allows you to put token from file into token container; 
 */   
    void define_token(Token &token);    
};

