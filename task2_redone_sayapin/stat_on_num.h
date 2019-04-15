#include "dyn_vec_token.h"

/**
 * This type allows you to store information about variable:
 * it`s type in char, and counter of something;
 */
struct Stats_On_Num {
    int (*inc_var_count) (struct Stats_On_Num *stat, struct Dynamic_Vec_Token *vec);
    int *counter_var;
    char *type_var;
    int size;
};
typedef struct Stats_On_Num Stats_On_Num;

/**
 * This function initializes object of type below:
 * type_var reflects unique name of variable in struct, 
 * count is number of something, depending on task;
 * returns NULL if there are problems with memory,
 * else pointer on struct;
 */
struct Stats_On_Num *
init_stats(char type_var, int count);

/**
 * This function make the memory given struct be free;
 */
void
finalize_stats(struct Stats_On_Num *stat);

/**
 * This function allows you to add variable into struct with type =
 * id_var, and counter = count_var;
 * It returns -1 if memory is full and free stat, else returns 0;
 */
int
add_var(struct Stats_On_Num *stat, char id_var, int count_var);

/**
 * This function allows you to get count information on type of your variable using
 * id_var;
 * It returns -1 if stat = NULL or there is no id_var is stat, else 0;
 */
int
get_var_count(struct Stats_On_Num *stat, char id_var);

/**
 * This function allows you to increase counter knowing id_var;
 * It returns -1 if stat = NULL or is_var is not in stat, else 0;
 */
int
inc_var_count(struct Stats_On_Num *stat, struct Dynamic_Vec_Token *vec);
