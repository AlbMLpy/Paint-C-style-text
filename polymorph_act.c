#include "polymorph_act.h"
#include "define_token.h"

void
polymorph_action_tokens(FILE *fd, Action *does)
{   
    struct Dynamic_Vec_Token *vec = initialize_vec_token();
    if (vec == NULL) {
        fprintf(stderr, "%s\n", "Memory error!");
        return;
    }
    if (give_token(vec, fd) == NULL) {
        fprintf(stderr, "%s\n", "Memory error!");
        return;
    }
    char type_token = get_type_token(vec);
    while (type_token != EOF_RET) {
        does->action(does, vec);
        set_end_token(vec, 0);
        if (give_token(vec, fd) == NULL) {
            fprintf(stderr, "%s\n", "Memory error!");
            return;
        }
        type_token = get_type_token(vec);
    }
    finalize_vec_token(vec);
    return;
}
