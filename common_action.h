#include "dyn_vec_token.h"

/**
 * This type is used to make universal interface for any functionality in the program;
 * Important: Anyone who would like to develop functions on tokens should
 * put main function on token to the same place as in Action type;
 * Besides, this type is opened to everyone who want to evolve functionality.
 */

#ifndef ACTION
#define ACTION
struct Action {
    int (*action) (struct Action *does, Dynamic_Vec_Token *vec);
};
typedef struct Action Action;
#endif
