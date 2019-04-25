#include "polymorph_act.h"
#include "Define_Token.h"

void
polymorph_action_tokens(FILE *fd, Action &action)
{   
    Define_Token define(fd);
    Token token;

    define.define_token(token);
    char type_token = token.get_type();
    while (type_token != EOF_RET) {
        action.action(token);
        token.set_end(0);
        define.define_token(token);
        type_token = token.get_type();
    }
    return;
}
