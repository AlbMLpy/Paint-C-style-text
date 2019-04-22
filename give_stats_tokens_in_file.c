#include "give_stats_tokens_in_file.h"
#include <stdio.h>

Stat_Token *
Stat_Token_init(Stat_Token *stat)
{
    stat->stat = Stats_On_Num_init_stats(IDENT, 0);
    if (stat->stat == NULL) {
        return NULL;
    }
    if (Stats_On_Num_add_var(stat->stat, CONST_CHAR, 0) == -1) {
        return NULL;
    }
    if (Stats_On_Num_add_var(stat->stat, CONST_STR, 0) == -1) {
        return NULL;
    }
    if (Stats_On_Num_add_var(stat->stat, CONST_INT, 0) == -1) {
        return NULL;
    }
    if (Stats_On_Num_add_var(stat->stat, COMMENT, 0) == -1) {
        return NULL;
    }
    if (Stats_On_Num_add_var(stat->stat, PUNCT, 0) == -1) {
        return NULL;
    }
    if (Stats_On_Num_add_var(stat->stat, KEY, 0) == -1) {
        return NULL;
    }
    if (Stats_On_Num_add_var(stat->stat, NO, 0) == -1) {
        return NULL;
    }
    return stat;  
}

void
Stat_Token_print_stat(Stat_Token *stat)
{
    printf("\nSTATISTICS ON FILE:\n");
    printf("\nstrange_tok = %d", Stats_On_Num_get_var_count(stat->stat, NO));
    printf("\nint_tok = %d", Stats_On_Num_get_var_count(stat->stat, CONST_INT));
    printf("\nkey_tok = %d", Stats_On_Num_get_var_count(stat->stat, KEY));
    printf("\nchar_tok = %d", Stats_On_Num_get_var_count(stat->stat, CONST_CHAR));
    printf("\nstr_tok = %d", Stats_On_Num_get_var_count(stat->stat, CONST_STR));
    printf("\nident_tok = %d", Stats_On_Num_get_var_count(stat->stat, IDENT));
    printf("\ncomment_tok = %d", Stats_On_Num_get_var_count(stat->stat, COMMENT));
    printf("\npunct_tok = %d\n", Stats_On_Num_get_var_count(stat->stat, PUNCT));
}

void
Stat_Token_finalize(Stat_Token *stat)
{
    Stats_On_Num_finalize_stats(stat->stat);
}

int
Stat_Token_inc_token(Stat_Token *stat, Dynamic_Vec_Token *vec)
{
   return Stats_On_Num_inc_var_count(stat->stat, Dynamic_Vec_Token_get_type_token(vec));
}    
