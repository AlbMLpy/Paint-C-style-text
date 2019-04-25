#include "Dynamic_Vec.h"

//These constants are essential to define token type

#ifndef CONST_INCLUDED
#define CONST_INCLUDED
enum { IDENT = 'i', NO = 'n', PUNCT = 'p',
        KEY = 'k', CONST_INT = 'd', CONST_CHAR = 'c',
        CONST_STR = 's', COMMENT = '/', INIT_TYPE = '#', EOF_RET = '$'};
#endif

/**
 * This type defines object for interacting with tokens in lexical analysis;
 */
class Token: public Dynamic_Vec  
{
    char type;
    int end;
public:
    Token();
    ~Token();
    Token(const Token &token);
/**
 * This function allows you to get a type of token defined above;
 */
    char get_type() const;

/**
 * This function allows you to set a type of token by token_type variable;
 * It is important to take types of token from set above;
 */
    void set_type(char token_type);

/**
 * This function allows you to get an end of token;
 */
    int get_end() const;

/**
 * This function allows you to set an end of token;
 */
    void set_end(int end_token);

/**
 * This function allows you to add the data into token;
 */
    void add_to(int data);

/**
 * This function allows you to get symbol data from any part of token 
 * via index; 
 */   
    int get_symbol(int index) const;

/**
 * This function prints token up to end of token to standart output;
 */
    void print() const;
};

