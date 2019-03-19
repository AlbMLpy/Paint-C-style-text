#include "analyzer.h"

int main(int argc, char ** argv)
{
    FILE *fp;
    if (argc == 1) {
        fprintf(stderr, "No file\n");
        return 1;
    }
    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Error with file\n");
        return 1;
    }
    analyzer(fp);
    fclose(fp);
    return 0;
}	
