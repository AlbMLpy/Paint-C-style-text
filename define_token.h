/// The entities from stdio.h are used in the next entities
#include <stdio.h>
#include "dyn_vec_token.h"

struct Define_Token {
    Dynamic_Vec_Token* (*act) (struct Define_Token *def, Dynamic_Vec_Token *vec);    
    FILE *fd;
};
typedef struct Define_Token Define_Token;

/**
 * Input parameters:
 *    - "vec" is a pointer on previously initialized object of type below;
 *    - "def" is a pointer on previously created Define_Token object;
 * Output parameters:
 *    - pointer on object of Dynamic_Vec_Token type;
 * Description:
 *    This function supposes initialization before using by hand!
 *    This function returns pointer object if there are no problems with memory, and
 *    NULL if the memory ran out: and set type of token: one from the set above;
 *    Besides, it shifts pointer of file; if EOF then token type=EOF_RET; 
 */
Dynamic_Vec_Token *
Define_Token_define_token(Define_Token *def, Dynamic_Vec_Token *vec);

