#include "give_stats_tokens_in_file.h"
#include <stdio.h>

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

struct Stats_On_Num *
init_stats_tokens(void)
{
    struct Stats_On_Num *stat = init_stats(IDENT, 0);
    if (stat == NULL) {
        return NULL;
    }
    stat->inc_var_count = inc_var_count;
    if (add_var(stat, CONST_CHAR, 0) == -1) {
        return NULL;
    }
    if (add_var(stat, CONST_STR, 0) == -1) {
        return NULL;
    }
    if (add_var(stat, CONST_INT, 0) == -1) {
        return NULL;
    }
    if (add_var(stat, COMMENT, 0) == -1) {
        return NULL;
    }
    if (add_var(stat, PUNCT, 0) == -1) {
        return NULL;
    }
    if (add_var(stat, KEY, 0) == -1) {
        return NULL;
    }
    if (add_var(stat, NO, 0) == -1) {
        return NULL;
    }
    return stat;  
}

void
print_stat(struct Stats_On_Num * stat)
{
    printf("\nSTATISTICS ON FILE:\n");
    printf("\nstrange_tok = %d", get_var_count(stat, NO));
    printf("\nint_tok = %d", get_var_count(stat, CONST_INT));
    printf("\nkey_tok = %d", get_var_count(stat, KEY));
    printf("\nchar_tok = %d", get_var_count(stat, CONST_CHAR));
    printf("\nstr_tok = %d", get_var_count(stat, CONST_STR));
    printf("\nident_tok = %d", get_var_count(stat, IDENT));
    printf("\ncomment_tok = %d", get_var_count(stat, COMMENT));
    printf("\npunct_tok = %d\n", get_var_count(stat, PUNCT));
}
