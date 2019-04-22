#include "dyn_vec_token.h"
#include "common_action.h"
/**
 * This type is used to perform painting of tokens in file.
 * Is supposes initialization by hand with function below.
 */
struct Painter {
    Action act;
};
typedef struct Painter Painter;

/**
 * This function is used to paint token in color based on token type.
 * Parameters:
 *    - "does" is used like this in C++ to hide functionality and specializations.
 *    - "vec" is a token being painted with colors fixed previously.
 */ 
int 
Painter_paint(Painter *does, Dynamic_Vec_Token *vec);
