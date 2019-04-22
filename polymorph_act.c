#include "polymorph_act.h"
#include "define_token.h"

void
polymorph_action_tokens(FILE *fd, Action *does)
{   
    Define_Token def;
    def.fd = fd;
    def.act = Define_Token_define_token;

    Dynamic_Vec_Token *vec = Dynamic_Vec_Token_initialize_vec_token();
    if (vec == NULL) {
        fprintf(stderr, "%s\n", "Memory error!");
        return;
    }
    if (def.act(&def, vec) == NULL) {
        fprintf(stderr, "%s\n", "Memory error!");
        return;
    }
    char type_token = Dynamic_Vec_Token_get_type_token(vec);
    while (type_token != EOF_RET) {
        does->action(does, vec);
        Dynamic_Vec_Token_set_end_token(vec, 0);
        if (def.act(&def, vec) == NULL) {
            fprintf(stderr, "%s\n", "Memory error!");
            return;
        }
        type_token = Dynamic_Vec_Token_get_type_token(vec);
    }
    Dynamic_Vec_Token_finalize_vec_token(vec);
    return;
}
