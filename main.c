#include "paint_tokens_in_file.h"
#include "give_stats_tokens_in_file.h"
#include "polymorph_act.h"
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
    
        Painter painter;
        painter.act.action = (int (*) (Action *, Dynamic_Vec_Token *)) Painter_paint;
        polymorph_action_tokens(fp, (Action*) &painter);
   
    } else if (*argv[2] == 's') {
     
        Stat_Token stat;
        stat.act.action = (int (*) (Action *, Dynamic_Vec_Token *)) Stat_Token_inc_token;
        if (Stat_Token_init(&stat) == NULL) {
            fprintf(stderr, "%s\n", "Memory error!");
            return 1;
        }
        polymorph_action_tokens(fp, (Action*) &stat);
        Stat_Token_print_stat(&stat);
        Stat_Token_finalize(&stat);

    } else {
        fclose(fp);
        fprintf(stderr, "Wrong mode!\n");
        return 1;
    }
    fclose(fp);
    return 0;
}	
