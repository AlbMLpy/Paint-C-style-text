//These constants are essential to define token type
#ifndef TOKENTYPE
#define TOKENTYPE

#include <string>
using std::string;
enum TokenType {IDENT, NONE, PUNCT, KEY, CONST_INT, CONST_CHAR,
        CONST_STR, COMMENT, EOF_RET};

/**
 * This type defines object for interacting with tokens in lexical analysis;
 */
class Token 
{
    string content;
    TokenType type;

public:
    Token(const string str, TokenType init_type);
    ~Token(){};
/**
 * This function allows you to get a type of token defined above;
 */
    TokenType get_type() const;

/**
 * This function allows you to get a string with content of token;
 */ 
    string get_string() const;
};    
#endif
