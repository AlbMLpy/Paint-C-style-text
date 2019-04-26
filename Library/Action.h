#include "Token.h"

/**
 * This type is used to make universal interface for any functionality in the program;
 * Besides, this type is opened to everyone who want to evolve functionality.
 */

#ifndef ACTION
#define ACTION
class Action {
public:    
    virtual int action(Token &token) = 0;
    virtual ~Action(){};
};
#endif
