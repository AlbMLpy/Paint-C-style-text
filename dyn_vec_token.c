#include "dynamic_vec.h"
#include "dyn_vec_token.h"
#include <stdlib.h>

struct Dynamic_Vec_Token
{
    struct Dynamic_Vec *vector;
    char token_type;
    int end_token;
};

char
get_type_token(struct Dynamic_Vec_Token *vec)
{
    if (vec == NULL) {
        return -1;
    }
    return vec->token_type;
}    

int
set_type_token(struct Dynamic_Vec_Token *vec, char token_type)
{
    if (vec == NULL) {
        return -1;
    }
    vec->token_type = token_type;
    return 0;
}    

int
get_end_token(struct Dynamic_Vec_Token *vec)
{
    if (vec == NULL) {
        return -1;
    }
    return vec->end_token;
}    

int
set_end_token(struct Dynamic_Vec_Token *vec, int end_token)
{
    if (vec == NULL) {
        return -1;
    }
    vec->end_token = end_token;
    return 0;
}    

struct Dynamic_Vec_Token *
initialize_vec_token(void)
{
    struct Dynamic_Vec_Token *vec = malloc(sizeof(*vec));
    if (vec == NULL) {
        return vec;
    }
    vec->vector = initialize_vec();
    if (vec->vector == NULL) {
        free(vec);
        return vec;
    }
    vec->token_type = INIT_TYPE;
    vec->end_token = 0;
    return vec;
}    

void
finalize_vec_token(struct Dynamic_Vec_Token *vec)
{
    if (vec != NULL) {
        finalize_vec(vec->vector);
        vec->token_type = INIT_TYPE;
        vec->end_token = 0;
        free(vec);
        vec = NULL;
    }
    return;
}    

struct Dynamic_Vec_Token *
add_to_token(struct Dynamic_Vec_Token *vec, int data)
{
    if (vec == NULL) {
        return vec;
    }
    set_value_vec(vec->vector, vec->end_token, data);
    if (vec->vector == NULL) {
        finalize_vec_token(vec);
        return vec;
    }
    vec->end_token++;
    return vec;
}    

int
get_sym_token(struct Dynamic_Vec_Token *vec, int index, int *data)
{
    if (vec == NULL) {
        return -1;
    }
    return get_value_vec(vec->vector, index, data);

}    

int
print_token(struct Dynamic_Vec_Token *vec)
{
    if (vec == NULL) {
        return -1;
    }
    return print_dyn_vec_text(vec->vector, 0, vec->end_token - 1);
}    










