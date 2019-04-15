#include <stdio.h>
#include "dyn_vec_token.h"

/**
 * This type is used to make universal interface for any functionality
 * in program;
 * Important: Anyone who want to develop any actions on tokens should
 * put main function on token the same place as in Action type;
 * Besides, this type is opened to everyone who want to evolve functionality.
 */ 
struct Action {
    int (*action) (struct Action *does, struct Dynamic_Vec_Token *vec);
};
typedef struct Action Action;

/**
 * This function allows you to make any actions on tokens if you
 * developed essential interface;
 * It supposes file to opened and pointed on by fd pointer;
 */ 
void
polymorph_action_tokens(FILE *fd, Action *does);
