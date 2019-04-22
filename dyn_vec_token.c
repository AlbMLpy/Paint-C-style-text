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
Dynamic_Vec_Token_get_type_token(Dynamic_Vec_Token *vec)
{
    if (vec == NULL) {
        return -1;
    }
    return vec->token_type;
}    

int
Dynamic_Vec_Token_set_type_token(Dynamic_Vec_Token *vec, char token_type)
{
    if (vec == NULL) {
        return -1;
    }
    vec->token_type = token_type;
    return 0;
}    

int
Dynamic_Vec_Token_get_end_token(Dynamic_Vec_Token *vec)
{
    if (vec == NULL) {
        return -1;
    }
    return vec->end_token;
}    

int
Dynamic_Vec_Token_set_end_token(Dynamic_Vec_Token *vec, int end_token)
{
    if (vec == NULL) {
        return -1;
    }
    vec->end_token = end_token;
    return 0;
}    

Dynamic_Vec_Token *
Dynamic_Vec_Token_initialize_vec_token(void)
{
    Dynamic_Vec_Token *vec = malloc(sizeof(*vec));
    if (vec == NULL) {
        return vec;
    }
    vec->vector = Dynamic_Vec_initialize_vec();
    if (vec->vector == NULL) {
        free(vec);
        return vec;
    }
    vec->token_type = INIT_TYPE;
    vec->end_token = 0;
    return vec;
}    

void
Dynamic_Vec_Token_finalize_vec_token(Dynamic_Vec_Token *vec)
{
    if (vec != NULL) {
        Dynamic_Vec_finalize_vec(vec->vector);
        vec->token_type = INIT_TYPE;
        vec->end_token = 0;
        free(vec);
        vec = NULL;
    }
    return;
}    

Dynamic_Vec_Token *
Dynamic_Vec_Token_add_to_token(Dynamic_Vec_Token *vec, int data)
{
    if (vec == NULL) {
        return vec;
    }
    Dynamic_Vec_set_value_vec(vec->vector, vec->end_token, data);
    if (vec->vector == NULL) {
        Dynamic_Vec_Token_finalize_vec_token(vec);
        return vec;
    }
    vec->end_token++;
    return vec;
}    

int
Dynamic_Vec_Token_get_sym_token(Dynamic_Vec_Token *vec, int index, int *data)
{
    if (vec == NULL) {
        return -1;
    }
    return Dynamic_Vec_get_value_vec(vec->vector, index, data);

}    

int
Dynamic_Vec_Token_print_token(Dynamic_Vec_Token *vec)
{
    if (vec == NULL) {
        return -1;
    }
    return Dynamic_Vec_print_dyn_vec_text(vec->vector, 0, vec->end_token - 1);
}    

