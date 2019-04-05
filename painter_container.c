#include "painter_container.h"
#include <stdio.h>

void
print_cont_in_color(void *container, int (*printer) (void *container), char *paint)
{   
    static char *no_paint_code = "\033[0m"; // cancel paint
    printf("%s", paint);
    printer(container);
    printf("%s", no_paint_code);
}



