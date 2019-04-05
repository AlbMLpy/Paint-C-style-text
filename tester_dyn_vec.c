#include "dynamic_vec.h"
#include <stdio.h>
int main(void)
{   
    int error = 0;
    struct Dynamic_Vec *vector = initialize_vec(&error);
    printf("%d", error);
    if (error == -1) {
        printf("error in init");
        return 0;
    }
    set_value_vec(vector, 0, 57);
    if (vector == NULL) {
        printf("error in set");
        return 0;
    }
    for (int i = 1; i<= 10; i++) {
        set_value_vec(vector, i, i+50);
    }
    set_value_vec(vector, -1, 2323);
    printf("hi\n");
    print_dyn_vec(vector, 0, 10);
    printf("\n");

    set_value_vec(vector, 1025, 57);
    printf("%d", size_vec(vector));
    int data = -1023;
    get_value_vec(vector, 1025, &data);
    printf("%c", data);
    printf("\nhi\n");
    print_dyn_vec(vector, 0, 3);
    printf("\nhi\n");
    print_dyn_vec(vector, 0, size_vec(vector)-1);
    finalize_vec(vector);
    return 0;

}    
