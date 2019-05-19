#include "Action.h"
#include <string>
/**
 * This class is used to perform painting of tokens typed Token.
 * Colors can not be changed by hand. Call for programmer;
 */
class Painter: public Action {
public:
/**
 * This function is used to paint token in color based on token type.
 *    - "token" is a reference on Token to be painted;
 */
    std::string action(Token &token) override;
    ~Painter(){}
};

