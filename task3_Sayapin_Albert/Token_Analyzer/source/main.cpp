#include "Painter.h"
#include "TokenCounter.h"
#include <cstdio>
#include "Analyzer.h"
#include "Action.h"
#include <iostream>

using std::cout;

void
polymorph_action_tokens(FILE *fd, Action &action)
{
    TokenType type = NONE;
    Analyzer analyzer(fd);
    do {
        Token token = analyzer.get_token();
        cout << action.action(token);
        type = token.get_type();
    } while (type != EOF_RET);
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
     
        TokenCounter token_counter;
        polymorph_action_tokens(fp, token_counter);

        printf("\nSTATISTICS ON FILE:\n");
        printf("\nstrange_tok = %d", token_counter[NONE]);
        printf("\nint_tok = %d", token_counter[CONST_INT]);
        printf("\nkey_tok = %d", token_counter[KEY]);
        printf("\nchar_tok = %d", token_counter[CONST_CHAR]);
        printf("\nstr_tok = %d", token_counter[CONST_STR]);
        printf("\nident_tok = %d", token_counter[IDENT]);
        printf("\ncomment_tok = %d", token_counter[COMMENT]);
        printf("\npunct_tok = %d\n", token_counter[PUNCT]);       

    } else {
        fclose(fp);
        fprintf(stderr, "Wrong mode!\n");
        return 1;
    }
    fclose(fp);
    return 0;
}	
