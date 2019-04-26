#include "Token.h"
#include <cstdlib>

Token::Token()
{
    type = INIT_TYPE;
    end = 0;
}

Token::Token(const Token& token): Dynamic_Vec(token) {
    end = token.end;
    type = token.type;
}

Token::~Token()
{
    type = INIT_TYPE;
    end = 0;
}

char
Token::get_type() const
{
    return type;
}    

void
Token::set_type(char token_type)
{
    type = token_type;
}    

int
Token::get_end() const
{
    return end;
}    

void
Token::set_end(int end_token)
{
    end = end_token;
}    

void
Token::add_to(int data)
{
    set_value(end, data);
    end++;
}    

int
Token::get_symbol(int index) const
{
    int data = 0;
    get_value(index, data);
    return data;
}    

void
Token::print() const
{
    print_text(0, end - 1);
}    

