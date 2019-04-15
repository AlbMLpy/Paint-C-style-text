#include "stat_on_num.h"
/**
 * Output parameters:
 *    - a pointer on type below if there are no problems with memory, else NULL;   
 * Description:
 *    This function initialize token stats object with type defined in define_token.h ;
 */
struct Stats_On_Num *
init_stats_tokens(void);

/**
 * Input parameters:
 *    - "stat" is a pointer on previously initializer object of type below;
 * Description:
 *    This function prints token stats with types difined in define_token.h;
 */
void
print_stat(struct Stats_On_Num *stat);
