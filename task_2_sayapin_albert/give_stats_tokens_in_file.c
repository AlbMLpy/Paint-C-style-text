#include "give_stats_tokens_in_file.h"
#include "stat_on_num.h"
#include "define_token.h"
#include <stdio.h>

/**
 * Output parameters:
 *    - a pointer on type below if there are no problems with memory, else NULL;   
 * Description:
 *    This function initialize token stats object with type defined in define_token.h ;
 */
static struct Stats_On_Num *
init_stats_tokens(void);

/**
 * Input parameters:
 *    - "stat" is a pointer on previously initializer object of type below;
 * Description:
 *    This function prints token stats with types difined in define_token.h;
 */
static void
print_stat(struct Stats_On_Num *stat);

void
give_number_tokens(FILE *fd)
{
    struct Dynamic_Vec_Token *vec = initialize_vec_token();
    if (vec == NULL) {
        fprintf(stderr, "%s\n", "Memory error!");
        return;
    }
    struct Stats_On_Num *stat = init_stats_tokens();
    if (stat == NULL) {
        fprintf(stderr, "%s\n", "Memory error!");
        return;
    }
    char type_token = get_type_token(vec);
    while (type_token != EOF_RET) {
        inc_var_count(stat, type_token);
        set_end_token(vec, 0);
        if (give_token(vec, fd) == NULL) {
            fprintf(stderr, "%s\n", "Memory error!");
            return;
        }
        type_token = get_type_token(vec);
    }
    print_stat(stat);
    finalize_vec_token(vec);
    finalize_stats(stat);
    return;
}

static struct Stats_On_Num *
init_stats_tokens(void)
{
    struct Stats_On_Num *stat = init_stats(IDENT, 0);
    if (stat == NULL) {
        return NULL;
    }
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

static void
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
