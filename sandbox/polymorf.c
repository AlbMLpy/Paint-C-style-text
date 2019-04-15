#include <stdio.h>

struct Action {
    int (*act) (struct Action *does, int *k);
};
typedef struct Action Action;


struct Inc_Var_Out {
    int (*inc) (struct Inc_Var_Out *does, int *k);
    void (*print_var_str) (struct Inc_Var_Out *does, int *k);
    char *str;
};
typedef struct Inc_Var_Out Inc_Var_Out;


struct Put {
    int (*put) (struct Put *does, int *k);
    int data;
    void (*print_data) (struct Put *does);
};
typedef struct Put Put;

int inc(Inc_Var_Out *does, int *k) 
{
    *k+=1;
    does->print_var_str(does, k);
    return 0;
}

void print_var_str(Inc_Var_Out *does, int *k)
{
    printf("\n%s;\n!!!%d!!!\n", does->str, *k);
    return;
}    

int put(Put *does, int *k)
{
    does->data = *k;
    does->print_data(does);
    return 0;
}    

void print_data(Put *does)
{
    printf("%d", does->data);
    return;
}

int action(Action *does, int *k)
{
    does->act(does, k);
    return 0;
}    

int main(void)
{
    int k = 13;
    
    Inc_Var_Out inc_to;
    inc_to.inc = inc;
    inc_to.print_var_str = print_var_str;
    inc_to.str = "Albert";
    
    Put put_to;
    put_to.put = put;
    put_to.data = -1;
    put_to.print_data = print_data;

    action((Action*) &put_to, &k);
    action((Action*) &inc_to, &k);
    action((Action*) &put_to, &k);

    return 0;
}    
