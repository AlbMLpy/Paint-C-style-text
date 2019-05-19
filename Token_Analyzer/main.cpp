#include "Painter.h"
#include "TokenCounter.h"
#include <cstdio>
#include "Analyzer.h"
#include "Action.h"

void
polymorph_action_tokens(FILE *fd, Action &action)
{   
    Analyzer analyzer(fd);
    do {
        Token token = analyzer.get_token();
        cout << action.action(token);        
    } while (token.get_type() != EOF_RET);
    return;
}

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
        polymorph_action_tokens(fp, painter);
   
    } else if (*argv[2] == 's') {
     
        Counter_Token token_stat;
        polymorph_action_tokens(fp, token_stat);
        token_stat.print_stat();

    } else {
        fclose(fp);
        fprintf(stderr, "Wrong mode!\n");
        return 1;
    }
    fclose(fp);
    return 0;
}	
