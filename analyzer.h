/// The entities from stdio.h are used in the next entities
#include <stdio.h>

/**
 * This function, painter, allows you to paint tokens in opened previously
 * file according to the rules of standart C.
 * Input parameter:
 *     - "fd" is of FILE* type and is a pointer on OPENED file;
 */ 
void painter(FILE *fd);

/**
 * This function, give_statistics, allows you to print amount of grouped tokens in opened previously
 * file according to the rules of standart C.
 * Input parameter:
 *     - "fd" is of FILE* type and is a pointer on OPENED file;
 */ 
void give_statistics(FILE *fd);
