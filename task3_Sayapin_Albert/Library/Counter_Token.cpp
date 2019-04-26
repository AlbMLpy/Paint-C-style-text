#include "Counter_Token.h"
#include <cstdio>

Counter_Token::Counter_Token():token_counter(IDENT, 0)
{
    token_counter.add_var(CONST_CHAR, 0);
    token_counter.add_var(CONST_STR, 0);
    token_counter.add_var(CONST_INT, 0);
    token_counter.add_var(COMMENT, 0);
    token_counter.add_var(PUNCT, 0);
    token_counter.add_var(KEY, 0);
    token_counter.add_var(NO, 0);
}

void
Counter_Token::print_stat() const
{
    printf("\nSTATISTICS ON FILE:\n");
    printf("\nstrange_tok = %d", token_counter.get_counter(NO));
    printf("\nint_tok = %d", token_counter.get_counter(CONST_INT));
    printf("\nkey_tok = %d", token_counter.get_counter(KEY));
    printf("\nchar_tok = %d", token_counter.get_counter(CONST_CHAR));
    printf("\nstr_tok = %d", token_counter.get_counter(CONST_STR));
    printf("\nident_tok = %d", token_counter.get_counter(IDENT));
    printf("\ncomment_tok = %d", token_counter.get_counter(COMMENT));
    printf("\npunct_tok = %d\n", token_counter.get_counter(PUNCT));
}

Counter_Token::~Counter_Token()
{

}    

int
Counter_Token::action(Token &token)
{
   return token_counter.inc_counter(token.get_type());
}    
