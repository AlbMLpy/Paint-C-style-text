#include "Counter.h"
#include "Action.h"

//This class is used to store statistics on tokens;
class Counter_Token: public Action 
{
    Counter token_counter;

public:
/**
 * This function creates Counter_Token object and put there:
 * Punctuator and counter = 0;
 * Comment and counter = 0;
 * Char constant and counter = 0;
 * String constant and counter = 0;
 * Integer constant and counter = 0;
 * Key word and counter = 0; 
 * Strange symbols and counter = 0;
 */   
    Counter_Token();
    ~Counter_Token();

/**
 * This function increases Counter_Token counter of token up to 1;
 */
    int action(Token &token);

 /**
 * This function prints Counter_Token information about all the content:
 * type/id of token and it`s counter;
 */   
    void print_stat() const;     
};
