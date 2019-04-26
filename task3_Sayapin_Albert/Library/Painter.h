#include "Action.h"
/**
 * This class is used to perform painting of tokens typed Token.
 * Colors can not be changed by hand. Call for programmer;
 */
class Painter: public Action {
    void print_colored(Token &token, const char *paint) const;     
public:
/**
 * This function is used to paint token in color based on token type.
 *    - "token" is a reference on Token to be painted;
 */
    int action(Token &token);
    Painter();
    virtual ~Painter();    
};

