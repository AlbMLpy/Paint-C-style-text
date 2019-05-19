#include "Counter.h"
#include "Action.h"
#include <vector>
using namespace std;
//This class is used to store statistics on tokens;
class TokenCounter: public Action 
{
    vector < Counter<TokenType> > token_counter;
public:
/**
 * This function creates Counter_Token object and put there:
 * Identificator and counter = 0;
 * Punctuator and counter = 0;
 * Comment and counter = 0;
 * Char constant and counter = 0;
 * String constant and counter = 0;
 * Integer constant and counter = 0;
 * Key word and counter = 0; 
 * Strange symbols and counter = 0;
 */   
    TokenCounter();
    ~TokenCounter(){};

/**
 * This function increases Counter_Token counter of token up to 1;
 */
    string action(Token &token) override;

/**
 * This function allows you to get counter via id of variable;
 * Returns -1 if id is not legal;
 */ 
 int operator[](TokenType type) const;   
};
