#include "Token.h"
#include <cstdio>
int main()
{
    Token token;
    printf("\n%c\n", token.get_type());
    printf("\n%d\n", token.get_end());
    
    token.set_type(PUNCT);
    printf("\n%c\n", token.get_type());
    printf("\n%d\n", token.get_end());

    token.add_to('*');
    printf("\n%c\n", token.get_type());
    printf("\n%d\n", token.get_end());

    printf("\n%d\n", token.get_symbol(0));
    printf("\n%d\n", token.get_symbol(1));

    token.print();
    
    Token token1 = token;

    printf("\n%c\n", token1.get_type());
    printf("\n%d\n", token1.get_end());
    token1.print();

    return 0;
}    
