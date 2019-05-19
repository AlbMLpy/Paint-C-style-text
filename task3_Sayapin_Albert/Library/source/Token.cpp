#include "Token.h"

Token::Token(const string str, TokenType init_type)
{
    content = str; 
    type = init_type;
}

TokenType
Token::get_type() const
{
    return type;
}    

string
Token::get_string() const
{
    return content;
}    

