/**
 * This function, print_cont_in_color, is used to put any container into standart
 * output stream in appropriate color;
 * Input parameters:
 *     - "container" is a pointer on any object that have printer function near;
 *     - "printer" is a pointer on a function that defined for the container to 
 *       print it on the screen;
 *     - "paint" is a string that decodes the color;
 * Output parameters:
 *     - this function does not have any parameters; 
 * This function supposes that container and printer functions are regular;
 */ 
void
print_cont_in_color(void *container, int (*printer) (void *container), char *paint);
