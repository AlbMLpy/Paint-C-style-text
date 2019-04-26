#include "Counter.h"
#include <cstdlib>

Counter::Counter(char type_variable = 'a', int count = 0)
{
    counter_var = (int*) malloc(sizeof(*counter_var));
    type_var = (char*) malloc(sizeof(*type_var));
    counter_var[0] = count;
    type_var[0] = type_variable;
    size = 1; 
}    


Counter::~Counter()
{
    free(counter_var);
    free(type_var);
}    

void
Counter::add_var(char id, int count)
{
    size++;    
    type_var = (char*) realloc(type_var, size);
    counter_var = (int*) realloc(counter_var, sizeof(*counter_var) * size);
    type_var[size - 1] = id;
    counter_var[size - 1] = count;
    return;
}    

int
Counter::get_counter(char id) const
{
    for (int i = 0; i < size; i++) {
        if (type_var[i] == id) {
            return counter_var[i];
        }
    }
    return -1; 
}

int
Counter::inc_counter(char id)
{
    for (int i = 0; i < size; i++) {
        if (type_var[i] == id) {
            counter_var[i] += 1;
            return 0;
        }
    }
    return -1;   
}    
