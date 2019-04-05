#include "painter_container.h"
#include "dyn_vec_token.h"
#include <stdio.h>

int main(void) 
{
    struct Dynamic_Vec_Token *vec = initialize_vec_token();

    char type_token = get_type_token(vec);
    int end_token = get_end_token(vec);
    printf("\n%c -type;\n%d -end;\n ", type_token, end_token);

    set_type_token(vec, '@');
    set_end_token(vec, 10);

    type_token = get_type_token(vec);
    end_token = get_end_token(vec);
    printf("\n%c -type;\n%d -end;\n ", type_token, end_token);
    
    add_to_token(vec, 'a');
    add_to_token(vec, 'l');
    add_to_token(vec, 'b');
    add_to_token(vec, 'e');
    add_to_token(vec, 'r');
    add_to_token(vec, 't');

    int data = 0;
    get_sym_token(vec, 0, &data);
    printf("%c", data);

    print_token(vec);
    printf("\n");
    print_cont_in_color((void*)vec, (void*) print_token, "\033[0;34m");
    finalize_vec_token(vec);
    return 0;
}    
