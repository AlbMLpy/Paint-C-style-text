#include "dyn_vec_token.h"

/**
 * This type is used to perform painting of tokens in file.
 * Is supposes initialization by hand with function below.
 */
struct Painter {
    int (*paint) (struct Painter *does, struct Dynamic_Vec_Token *vec);
    void (*print_token_in_color) (struct Dynamic_Vec_Token *vec);
};
typedef struct Painter Painter;

/**
 * This function is used to paint token in color based on token type.
 * Parameters:
 *    - "does" is used like this in C++ to hide functionality and specializations.
 *    - "vec" is a token being painted with colors fixed previously.
 */ 
int 
paint(Painter *does, struct Dynamic_Vec_Token *vec);

/**
 * This function paints token in color.
 * It needs only token container.
 * This one helps paint to realize all the functionality.
 */ 
void
print_token_in_color(struct Dynamic_Vec_Token *vec);
