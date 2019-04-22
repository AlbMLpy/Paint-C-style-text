//These constants are essential to define tokens type

#ifndef CONST_INCLUDED
#define CONST_INCLUDED
enum { IDENT = 'i', NO = 'n', PUNCT = 'p',
        KEY = 'k', CONST_INT = 'd', CONST_CHAR = 'c',
        CONST_STR = 's', COMMENT = '/', INIT_TYPE = '#', EOF_RET = '$'};
#endif

/**
 * This type defines object for interacting with tokens in lexical analysis;
 */
struct Dynamic_Vec_Token;
typedef struct Dynamic_Vec_Token Dynamic_Vec_Token;
/**
 * This function allows you to get a type of token vector;
 * If vec == NULL, function returns -1, else type in char,
 * commonly defined above;
 */ 
char
Dynamic_Vec_Token_get_type_token(Dynamic_Vec_Token *vec);

/**
 * This function allows you to set a type of token vector;
 * If vec == NULL, function returns -1, else 0 and sets type;
 */
int
Dynamic_Vec_Token_set_type_token(Dynamic_Vec_Token *vec, char token_type);

/**
 * This function allows you to get an end of token vector;
 * If vec == NULL, function returns -1, else end in int,
 */
int
Dynamic_Vec_Token_get_end_token(Dynamic_Vec_Token *vec);

/**
 * This function allows you to set an end of token vector;
 * If vec == NULL, function returns -1, else 0 and sets end of token;
 */
int
Dynamic_Vec_Token_set_end_token(Dynamic_Vec_Token *vec, int end_token);

/**
 * This function initializes vector with INIT_TYPE, end of token = 0;
 * If there are problems with memory it returns NULL, else pointer on 
 * appropriate container;
 */
Dynamic_Vec_Token *
Dynamic_Vec_Token_initialize_vec_token(void);

/**
 * This function make the memory given to container be free;
 * vec = NULL;
 */
void
Dynamic_Vec_Token_finalize_vec_token(Dynamic_Vec_Token *vec);

/**
 * This function allows you to add the data into token;
 * If there are no problems with memory it increase end of token 
 * and put data into container, else make vec be free and returns NULL;
 */
Dynamic_Vec_Token *
Dynamic_Vec_Token_add_to_token(Dynamic_Vec_Token *vec, int data);

/**
 * This function returns -1 if vec == NULL, else it returns 0 if everything is fine, 
 * *data = data in index;
 */
int
Dynamic_Vec_Token_get_sym_token(Dynamic_Vec_Token *vec, int index, int *data);

/**
 * This function prints token up to end of token to standart output;
 */
int
Dynamic_Vec_Token_print_token(Dynamic_Vec_Token *vec);

