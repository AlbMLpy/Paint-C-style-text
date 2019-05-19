#include "TokenCounter.h"

TokenCounter::TokenCounter()
{
    token_counter.push_back(Counter<TokenType>(IDENT));
    token_counter.push_back(Counter<TokenType>(KEY));
    token_counter.push_back(Counter<TokenType>(CONST_CHAR));
    token_counter.push_back(Counter<TokenType>(CONST_STR));
    token_counter.push_back(Counter<TokenType>(CONST_INT));
    token_counter.push_back(Counter<TokenType>(COMMENT));
    token_counter.push_back(Counter<TokenType>(PUNCT));
    token_counter.push_back(Counter<TokenType>(NONE));
}

int
TokenCounter::operator[](TokenType type) const
{
    for (unsigned i = 0; i < token_counter.size(); i++) {
        if (token_counter[i].get_id() == type) {
            return token_counter[i].get_counter();
        }
    }
    return -1;
}

string
TokenCounter::action(Token &token) 
{
    TokenType type = token.get_type();
    for (unsigned i = 0; i < token_counter.size(); i++) {
        if (token_counter[i].get_id() == type) {
            token_counter[i].inc_counter();
        }
    }
    return string("");
}    
