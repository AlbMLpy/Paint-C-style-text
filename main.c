#include "analyzer.h"

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
        painter(fp);
    } else if (*argv[2] == 's') {
        give_statistics(fp);
    } else {
        fclose(fp);
        fprintf(stderr, "Wrong mode!\n");
        return 1;
    }
    fclose(fp);
    return 0;
}	
