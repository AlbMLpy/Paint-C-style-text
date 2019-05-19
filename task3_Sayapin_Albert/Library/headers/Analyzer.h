/// The entities from stdio.h are used in the next entities
#include <cstdio>
#include "Token.h"

/**
 * This class is used for work with file to define token as in standart
 * of C language.
 */ 
class Analyzer {
    FILE *fd;

    Token int_dec_token(string &buffer);
    Token int_oct_token(string &buffer);
    Token char_token(string &buffer);
    Token string_token(string &buffer);
    Token ident_token(string &buffer);
    Token comment_new_token(string &buffer);
    Token comment_old_token(string &buffer);
    Token punct_token(string &buffer);
    bool is_key(string &buffer);
    bool hex_only(string &buffer);
    bool oct_less_eq_3(string &buffer);
    bool u_4_8_hex(string &buffer);    
public:
    Analyzer(FILE *fp);
    ~Analyzer() {}; 
/**
 * This function allows you to get token from file; 
 */   
    Token get_token();    
};

