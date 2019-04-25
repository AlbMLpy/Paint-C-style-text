#include "Token.h"

/**
 * This type is used to make universal interface for any functionality in the program;
 * Important: Anyone who would like to develop functions on tokens should
 * put main function on token to the same place as in Action type;
 * Besides, this type is opened to everyone who want to evolve functionality.
 */

#ifndef ACTION
#define ACTION
class Action {
public:    
    virtual int action(Token &vec) = 0;
};
#endif
