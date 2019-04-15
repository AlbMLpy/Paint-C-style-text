#include "painter_container.h"
#include <stdio.h>

void
print_cont_in_color(
        struct Dynamic_Vec_Token *container,
        int (*printer) (struct Dynamic_Vec_Token *container),
        char *paint)
{   
    static char *no_paint_code = "\033[0m"; // cancel paint
    printf("%s", paint);
    printer(container);
    printf("%s", no_paint_code);
}



