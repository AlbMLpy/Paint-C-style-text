#include "stat_on_num.h"
#include <stdlib.h>

Stats_On_Num *
Stats_On_Num_init_stats(char type_var, int count)
{
    Stats_On_Num *stat = malloc(sizeof(*stat));
    if (stat == NULL) {
        return stat;
    }
    stat->counter_var = malloc(sizeof(*(stat->counter_var)));
    if (stat->counter_var == NULL) {
        Stats_On_Num_finalize_stats(stat);
        return stat;
    }
    stat->type_var = malloc(sizeof(*(stat->type_var)));
    if (stat->type_var == NULL) {
        Stats_On_Num_finalize_stats(stat);
        return stat;
    }
    stat->counter_var[0] = count;
    stat->type_var[0] = type_var;
    stat->size = 1;
    return stat; 
}    

void
Stats_On_Num_finalize_stats(Stats_On_Num *stat)
{
    if (stat == NULL) {
        return;
    }
    free(stat->counter_var);
    free(stat->type_var);
    free(stat);
    stat = NULL;
    return;
}    

int
Stats_On_Num_add_var(Stats_On_Num *stat, char id_var, int count_var)
{
    if (stat == NULL) {
        return -1;
    }
    stat->size++;    
    stat->type_var = realloc(stat->type_var, stat->size);
    if (stat->type_var == NULL) {
        Stats_On_Num_finalize_stats(stat);
        return -1;
    }    
    stat->counter_var = realloc(stat->counter_var, sizeof(*(stat->counter_var)) * stat->size);
    if (stat->counter_var == NULL) {
        Stats_On_Num_finalize_stats(stat);
        return -1;
    }
    stat->type_var[(stat->size) - 1] = id_var;
    stat->counter_var[(stat->size) - 1] = count_var;
    return 0;
}    

int
Stats_On_Num_get_var_count(Stats_On_Num *stat, char id_var)
{
    if (stat == NULL) {
        return -1;
    }
    for (int i = 0; i < stat->size; i++) {
        if (stat->type_var[i] == id_var) {
            return stat->counter_var[i];
        }
    }
    return -1; 
}

int
Stats_On_Num_inc_var_count(struct Stats_On_Num *stat, char id_var)
{
    if (stat == NULL) {
        return -1;
    }
    for (int i = 0; i < stat->size; i++) {
        if (stat->type_var[i] == id_var) {
            stat->counter_var[i] += 1;
            return 0;
        }
    }
    return -1;   
}    
