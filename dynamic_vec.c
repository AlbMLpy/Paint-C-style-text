#include "dynamic_vec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {INIT_SIZE = 1024, POW_SIZE = 2};

struct Dynamic_Vec 
{
    int *container;
    int size;    
};

int
Dynamic_Vec_size_vec(Dynamic_Vec *vec)
{
    if (vec == NULL) {
        return -1;
    }
    return vec->size;
}    

Dynamic_Vec * 
Dynamic_Vec_initialize_vec(void)
{
    Dynamic_Vec *vec = malloc(sizeof(*vec));
    if (vec == NULL) {
        return vec;
    }
    vec->container = malloc(sizeof(*(vec->container)) * INIT_SIZE);
    if (vec->container == NULL) {
        Dynamic_Vec_finalize_vec(vec);
        return vec;    
    }
    memset(vec->container, 0, sizeof(vec->container[0]) * INIT_SIZE);
    vec->size = INIT_SIZE;
    return vec;
}    

void
Dynamic_Vec_finalize_vec(Dynamic_Vec *vec)
{
    if (vec != NULL) {
        free(vec->container);
        vec->size = 0;
        free(vec);
        vec = NULL;
    }    
    return;
}

Dynamic_Vec *
Dynamic_Vec_set_value_vec(Dynamic_Vec *vec, int index, int data)
{
    if (vec == NULL) {
        return vec;
    }
    if (index < 0) {
        return vec;
    }
    if (index >= vec->size) {
        vec->size = vec->size * POW_SIZE;
        vec->container = realloc(vec->container, vec->size * sizeof(*(vec->container)));
        if (vec->container == NULL) {
            Dynamic_Vec_finalize_vec(vec);
            vec = NULL;
            return vec;
        }
        int offset = vec->size / POW_SIZE;
        memset(vec->container + offset, 0, sizeof(vec->container[0]) * offset);
    }
    vec->container[index] = data;
    return vec;
}    

int 
Dynamic_Vec_get_value_vec(Dynamic_Vec *vec, int index, int *data)
{
    if (vec == NULL) {
        return -1;
    }
    if (index < 0 || index > vec->size) {
        return -1;
    }
    *data = vec->container[index];
    return 0;
}    

int
Dynamic_Vec_print_dyn_vec_digit(Dynamic_Vec *vec, int index_begin, int index_end)
{
    if (vec == NULL) {
        return -1;
    }
    if (index_begin > index_end) {
        return -1;
    }
    if (index_begin < 0) {
        return -1;
    }
    if (index_end > vec->size) {
        return -1;
    }
    for (int i = index_begin; i <= index_end; i++) {
        printf("%d ", vec->container[i]);
    }
    return 0;
}    

int
Dynamic_Vec_print_dyn_vec_text(Dynamic_Vec *vec, int index_begin, int index_end)
{
    if (vec == NULL) {
        return -1;
    }
    if (index_begin > index_end) {
        return -1;
    }
    if (index_begin < 0) {
        return -1;
    }
    if (index_end > vec->size) {
        return -1;
    }
    fwrite(vec->container + index_begin, sizeof(*(vec->container)), index_end - index_begin + 1, stdout);
    return 0;
}



