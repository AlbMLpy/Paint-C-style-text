#include "paint_tokens_in_file.h"
#include "give_stats_tokens_in_file.h"
#include <stdio.h>

int main(int argc, char ** argv)
{
    FILE *fp;
    if (argc < 3) {
        fprintf(stderr, "Wrong parameters!\n");
        return 1;
    }
    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Error with file!\n");
        return 1;
    }
    if (*argv[2] == 'p') {
        print_colored_tokens(fp);
    } else if (*argv[2] == 's') {
        give_number_tokens(fp);
    } else {
        fclose(fp);
        fprintf(stderr, "Wrong mode!\n");
        return 1;
    }
    fclose(fp);
    return 0;
}	
