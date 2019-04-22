#include "stat_on_num.h"
#include "common_action.h"
#include "dyn_vec_token.h"

struct Stat_Token {
    Action act;
    Stats_On_Num *stat;
};
typedef struct Stat_Token Stat_Token;

/**
 * Input parameters:
 *    - a pointer on object of Stat_Token type created in static memory;
 * Output parameters:
 *    - a pointer on object of Stat_Token type if there are no problems with memory, else NULL;   
 * Description:
 *    This function initialize Stat_Token object with fields: 
 *    creates Stats_On_Num object with cell filled with variables of 8 previously
 *    given tokens: identificators, comments, char, string, punctuator, key, int, none;
 *    Action act field should be filled by hand;
 */
Stat_Token *
Stat_Token_init(Stat_Token *stat);

/**
 * Input parameters:
 *    - "stat" is a pointer on previously initialized object of type Stat_Token;
 * Description:
 *    This function prints token stats;
 */
void
Stat_Token_print_stat(Stat_Token *stat);

/**
 * Input parameters:
 *    - "stat" is a pointer on previously initialized object of type Stat_Token;
 * Description:
 *    This function frees Stat_Token stat pointer;
 */
void
Stat_Token_finalize(Stat_Token *stat);

/**
 * Input parameters:
 *    - "stat" is a pointer on previously initialized object of type Stat_Token;
 *    - "vec" is a pointer on Dynamic_Vec_Token object;
 * Description:
 *    This function increases Stat_Token stat counter of token up to 1;
 */
int
Stat_Token_inc_token(Stat_Token *stat, Dynamic_Vec_Token *vec);


