#include "Dynamic_Vec.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

enum {INIT_SIZE = 1024, POW_SIZE = 2};

int
Dynamic_Vec::get_size() const
{
    return size;
}    

Dynamic_Vec::Dynamic_Vec(const Dynamic_Vec& vec) 
{
    container = (int*) malloc(sizeof(*container) * INIT_SIZE);
    for (int i = 0; i <= vec.size; i++) {
        container[i] = vec.container[i];
    }
    size = vec.size;
}    

Dynamic_Vec::Dynamic_Vec()
{
    container = (int*) malloc(sizeof(*container) * INIT_SIZE);
    memset(container, 0, sizeof(container[0]) * INIT_SIZE);
    size = INIT_SIZE;
}    

Dynamic_Vec::~Dynamic_Vec()
{
    free(container);
    container = NULL;
    size = 0;
}

int
Dynamic_Vec::set_value(int index, int data)
{
    if (index < 0) {
        return -1;
    }
    while (index >= size) {
        size = size * POW_SIZE;
        container = (int*) realloc(container, size * sizeof(*container));
        int offset = size / POW_SIZE;
        memset(container + offset, 0, sizeof(container[0]) * offset);
    }
    container[index] = data;
    return 0;
}    

int 
Dynamic_Vec::get_value(int index, int &data) const
{
    if (index < 0 || index > size) {
        return -1;
    }
    data = container[index];
    return 0;
}    

int
Dynamic_Vec::print_digit(int index_begin, int index_end) const
{
    if (index_begin > index_end) {
        return -1;
    }
    if (index_begin < 0) {
        return -1;
    }
    if (index_end > size) {
        return -1;
    }
    for (int i = index_begin; i <= index_end; i++) {
        printf("%d ", container[i]);
    }
    return 0;
}    

int
Dynamic_Vec::print_text(int index_begin, int index_end) const
{
    if (index_begin > index_end) {
        return -1;
    }
    if (index_begin < 0) {
        return -1;
    }
    if (index_end > size) {
        return -1;
    }
    fwrite(container + index_begin, sizeof(*container), index_end - index_begin + 1, stdout);
    return 0;
}

