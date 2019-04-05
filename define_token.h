/// The entities from stdio.h are used in the next entities
#include <stdio.h>
#include "dyn_vec_token.h"

/* These constants reflect tokens
enum { IDENT = 'i', NO = 'n', PUNCT = 'p',
        KEY = 'k', CONST_INT = 'd', CONST_CHAR = 'c', 
        CONST_STR = 's', COMMENT = '/', INIT_TYPE = '#', EOF_RET = '$'};
*/

/**
 * Input parameters:
 *    - "vec" is a pointer on previously initialized object of type below;
 *    - "fd" is a pointer on previously opened file;
 * Output parameters:
 *    - pointer on object typed below;
 * Description:
 *    This function returns pointer object if there are no problems with memory, and
 *    NULL if the memory ran out: and set type of token: one from the set above;
 *    Besides, it shifts pointer of file; if EOF then token type=EOF_RET; 
 */
struct Dynamic_Vec_Token *
give_token(struct Dynamic_Vec_Token *vec, FILE *fd);

