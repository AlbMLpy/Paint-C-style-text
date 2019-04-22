#include "define_token.h"
#include <string.h>
#include <ctype.h>

// These constants reflect sizes of key words
enum { ONE_LETTER = 1, TWO_LETTERS = 2, SIZE_UNS = 8, SIZE_VOID = 4,
        SIZE_ATOM = 7, SIZE_BOOL = 5, SIZE_COMPL = 8, SIZE_GEN = 8,
        SIZE_IMAG = 10, SIZE_NORET = 9, SIZE_STASS = 14, SIZE_THR = 13,
        SIZE_WHILE = 5, SIZE_VOLAT = 8, SIZE_ALIGNAS = 8, SIZE_ALIGNOF = 8,
        POS_TO_SIZE = 1 };

// These constants reflect requrements of design
enum { SH_ONE_BK = -1, DIV_F = 4 };

// These constants reflect requrements of design
enum { TRUE = 1, FALSE = 0, SIZE_SET_ID_CH_STR = 2, 
       SIZE_SET_PUNCT = 13, SIZE_SET_SIM_ESC = 11, SIZE_UCN = 9 };

// Need these sets according to standart C
static char punctuators[] = { '+', '-', '&', '*', '~', '!', '/', '%', '<', '>', '^', '|', '=' };
static char set_id_ch_str[] = { 'L', 'U' };
static char simple_escape[] = { '\'', '\"', '?', '\\', 'a', 'b', 'f', 'n', 'r', 't', 'v' };

/**
 * Input parameters:
 *    - "vec" is a pointer on previously initialized object of type below;
 *    - "fd" is a pointer on previously opened file;
 * Output parameters:
 *    - pointer on object typed below;
 * Description:
 *    This function returns pointer object if there are no problems with memory, and
 *    NULL if the memory ran out: and set type of token: CONST_INT if token is regular, NO in contrast;
 */
static Dynamic_Vec_Token *
int_dec_token(Dynamic_Vec_Token *vec, FILE *fd);

/**
 * Input parameters:
 *    - "vec" is a pointer on previously initialized object of type below;
 *    - "fd" is a pointer on previously opened file;
 * Output parameters:
 *    - pointer on object typed below;
 * Description:
 *    This function returns pointer object if there are no problems with memory, and
 *    NULL if the memory ran out: and set type of token: CONST_INT if token is regular, NO in contrast;
 */
static Dynamic_Vec_Token *
int_oct_token(Dynamic_Vec_Token *vec, FILE *fd);

/**
 * Input parameters:
 *    - "vec" is a pointer on previously initialized object of type below;
 *    - "fd" is a pointer on previously opened file;
 * Output parameters:
 *    - pointer on object typed below;
 * Description:
 *    This function returns pointer object if there are no problems with memory, and
 *    NULL if the memory ran out: and set type of token: CONST_CHAR if token is regular, NO in contrast;
 */
static Dynamic_Vec_Token *
char_token(Dynamic_Vec_Token *vec, FILE *fd);

/**
 * Input parameters:
 *    - "vec" is a pointer on previously initialized object of type below;
 *    - "fd" is a pointer on previously opened file;
 * Output parameters:
 *    - pointer on object typed below;
 * Description:
 *    This function returns pointer object if there are no problems with memory, and
 *    NULL if the memory ran out: and set type of token: CONST_STR if token is regular, NO in contrast;
 */
static Dynamic_Vec_Token *
string_token(Dynamic_Vec_Token *vec, FILE *fd);

/**
 * Input parameters:
 *    - "vec" is a pointer on previously initialized object of type below;
 *    - "fd" is a pointer on previously opened file;
 * Output parameters:
 *    - pointer on object typed below;
 * Description:
 *    This function returns pointer object if there are no problems with memory, and
 *    NULL if the memory ran out: and set type of token: IDENT if token is regular, NO in contrast;
 */
static Dynamic_Vec_Token *
ident_token(Dynamic_Vec_Token *vec, FILE *fd);

/**
 * Input parameters:
 *    - "vec" is a pointer on previously initialized object of type below;
 *    - "fd" is a pointer on previously opened file;
 * Output parameters:
 *    - pointer on object typed below;
 * Description:
 *    This function returns pointer object if there are no problems with memory, and
 *    NULL if the memory ran out: and set type of token: COMMENT if token is regular, NO in contrast;
 */
static Dynamic_Vec_Token *
comment_new_token(Dynamic_Vec_Token *vec, FILE *fd);

/**
 * Input parameters:
 *    - "vec" is a pointer on previously initialized object of type below;
 *    - "fd" is a pointer on previously opened file;
 * Output parameters:
 *    - pointer on object typed below;
 * Description:
 *    This function returns pointer object if there are no problems with memory, and
 *    NULL if the memory ran out: and set type of token: COMMENT if token is regular, NO in contrast;
 */
static Dynamic_Vec_Token *
comment_old_token(Dynamic_Vec_Token *vec, FILE *fd);

/**
 * Input parameters:
 *    - "vec" is a pointer on previously initialized object of type below;
 *    - "fd" is a pointer on previously opened file;
 * Output parameters:
 *    - pointer on object typed below;
 * Description:
 *    This function returns pointer object if there are no problems with memory, and
 *    NULL if the memory ran out: and set type of token: PUNCT if token is regular, NO in contrast;
 */
static Dynamic_Vec_Token *
punct_token(Dynamic_Vec_Token *vec, FILE *fd);

/**
 * Input parameters:
 *    - "vec" is a pointer on previously initialized object of type below;
 *    - "set" is a pointer on set that is of the same size as vec;
 * Output parameters:
 *    - returns 1 if sets are equal;
 *    - returns 0 if sets are not equal;
 * Description: 
 *    This function compares two sets of equal size;
 */
static int
equal_sets(Dynamic_Vec_Token *vec, char *set);

/**
 * Input parameters:
 *    - "vec" is a pointer on previously initialized object of type below;
 * Output parameters:
 *    - returns 1 if token is equal to key token;
 *    - returns 0 if token is not equal to key token;
 * Description: 
 *    This function check if input token is a key token;
 */ 
static int
is_key(Dynamic_Vec_Token *vec);

/**
 * Input parameters:
 *    - "vec" is a pointer on previously initialized object of type below;
 *    - "fd" is a pointer on previously opened file;
 * Output parameters:
 *    - pointer on object typed below;
 * Description:
 *    This function returns pointer object if there are no problems with memory, and
 *    NULL if the memory ran out: and set type of token: INIT_TYPE if token is regular, NO in contrast;
 *    It pulls only heximal digits into token else token type=NO;
 */
static Dynamic_Vec_Token *
hex_only(Dynamic_Vec_Token *vec, FILE *fd);

/**
 * Input parameters:
 *    - "vec" is a pointer on previously initialized object of type below;
 *    - "fd" is a pointer on previously opened file;
 * Output parameters:
 *    - pointer on object typed below;
 * Description:
 *    This function returns pointer object if there are no problems with memory, and
 *    NULL if the memory ran out: and set type of token: INIT_TYPE if token is regular, NO in contrast;
 *    It pulls only 0 < x <= 3 octuple digits into token else token type=NO;
 */
static Dynamic_Vec_Token *
oct_less_eq_3(Dynamic_Vec_Token *vec, FILE *fd);

/**
 * Input parameters:
 *    - "vec" is a pointer on previously initialized object of type below;
 *    - "fd" is a pointer on previously opened file;
 * Output parameters:
 *    - pointer on object typed below;
 * Description:
 *    This function returns pointer object if there are no problems with memory, and
 *    NULL if the memory ran out: and set type of token: INIT_TYPE if token is regular, NO in contrast;
 *    It pulls only 4 or 8 heximal digits into token else token type=NO;
 */
static Dynamic_Vec_Token *
u_4_8_hex(Dynamic_Vec_Token *vec, FILE *fd);


static Dynamic_Vec_Token *
int_dec_token(Dynamic_Vec_Token *vec, FILE *fd)
{
    int init = 0;
    while (TRUE) {       
        init = fgetc(fd);
        if (isdigit(init)) {
            if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                return NULL;
            }
            continue;
        } else {
            Dynamic_Vec_Token_set_type_token(vec, CONST_INT);
            fseek(fd, SH_ONE_BK, SEEK_CUR);   
            return vec;
        }
    }        
}   

static Dynamic_Vec_Token *
int_oct_token(Dynamic_Vec_Token *vec, FILE *fd)
{
    int init = 0;
    while (TRUE) {
        init = fgetc(fd);
        if (isdigit(init) && init != '9' && init != '8') {
            if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                return NULL;
            }
            continue;
        } else {
            Dynamic_Vec_Token_set_type_token(vec, CONST_INT);
            fseek(fd, SH_ONE_BK, SEEK_CUR);
            return vec;
        }           
    }
}   

static Dynamic_Vec_Token *
char_token(Dynamic_Vec_Token *vec, FILE *fd)
{   
    int init = 0;
    int state_begin = 0;    
    init = fgetc(fd);
    if (init == '\'' || init == '\n') {
        if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
            return NULL;
        }
        Dynamic_Vec_Token_set_type_token(vec, NO);
        return vec;
    }   
    if (init == EOF) {
        Dynamic_Vec_Token_set_type_token(vec, NO);
        return vec;
    }
    while (TRUE) {
        if (state_begin) {
            init = fgetc(fd);
        }
        state_begin++;
        switch (init) {
        case '\'':
            if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                return NULL;
            }
            Dynamic_Vec_Token_set_type_token(vec, CONST_CHAR);
            return vec;
        case '\\':
            if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                return NULL;
            }
            init = fgetc(fd);
            switch (init) {
            case 'U':
            case 'u':
                fseek(fd, SH_ONE_BK, SEEK_CUR);   
                if (u_4_8_hex(vec, fd) == NULL) {
                    return NULL;
                }
                if (Dynamic_Vec_Token_get_type_token(vec) != INIT_TYPE) {
                    return vec;
                }
                continue;
            case 'x':
                if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                    return NULL;
                } 
                if (hex_only(vec, fd) == NULL) {
                    return NULL;
                }
                if (Dynamic_Vec_Token_get_type_token(vec) != INIT_TYPE) {
                    return vec;
                }
                continue;
            default:
                if (isdigit(init) && init != '8' && init != '9') {
                    fseek(fd, SH_ONE_BK, SEEK_CUR);
                    if (oct_less_eq_3(vec, fd) == NULL) {
                        return NULL;
                    }
                    if (Dynamic_Vec_Token_get_type_token(vec) != INIT_TYPE) {
                        return vec;
                    }
                    continue;
                } else if (memchr(simple_escape, init, SIZE_SET_SIM_ESC) != NULL) {
                    if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                        return NULL;
                    }  
                    continue;
                } else {
                    fseek(fd, SH_ONE_BK, SEEK_CUR);
                    Dynamic_Vec_Token_set_type_token(vec, NO);
                    return vec;
                }
            }
        default:
            if (init == EOF) {
                Dynamic_Vec_Token_set_type_token(vec, NO);
                return vec;
            }
            if (init == '\n') {
                if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                    return NULL;
                }
                Dynamic_Vec_Token_set_type_token(vec, NO);
                return vec;
            }  
            if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                return NULL;
            }
            continue;  
        }
    }
}       

static Dynamic_Vec_Token *
string_token(Dynamic_Vec_Token *vec, FILE *fd)
{
    int init = 0;    
    while (TRUE) {
        init = fgetc(fd);
        switch (init) {
        case '\"':
            if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                return NULL;
            }
            Dynamic_Vec_Token_set_type_token(vec, CONST_STR);
            return vec;
        case '\\':
            if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                return NULL;
            }
            init = fgetc(fd);
            switch (init) {
            case 'U':
            case 'u':
                fseek(fd, SH_ONE_BK, SEEK_CUR);   
                if (u_4_8_hex(vec, fd) == NULL) {
                    return NULL;
                }
                if (Dynamic_Vec_Token_get_type_token(vec) != INIT_TYPE) {
                    return vec;
                }
                continue;
            case 'x':
                if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                    return NULL;
                } 
                if (hex_only(vec, fd) == NULL) {
                    return NULL;
                }
                if (Dynamic_Vec_Token_get_type_token(vec) != INIT_TYPE) {
                    return vec;
                }
                continue;
            default:
                if (isdigit(init) && init != '8' && init != '9') {
                    fseek(fd, SH_ONE_BK, SEEK_CUR);
                    if (oct_less_eq_3(vec, fd) == NULL) {
                        return NULL;
                    }
                    if (Dynamic_Vec_Token_get_type_token(vec) != INIT_TYPE) {
                        return vec;
                    }
                    continue;
                } else if (memchr(simple_escape, init, SIZE_SET_SIM_ESC) != NULL) {
                    if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                        return NULL;
                    }  
                    continue;
                } else {
                    Dynamic_Vec_Token_set_type_token(vec, NO);
                    return vec;
                }
            }
        default:
            if (init == EOF) {
                Dynamic_Vec_Token_set_type_token(vec, NO);
                return vec;
            }
            if (init == '\n') {
                if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                    return NULL;
                }
                Dynamic_Vec_Token_set_type_token(vec, NO);
                return vec;
            }
            if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                return NULL;
            }  
            continue;  
        }
    }
}           

static Dynamic_Vec_Token *
ident_token(Dynamic_Vec_Token *vec, FILE *fd)
{ 
    int init = 0;
    while (TRUE) {
        init = fgetc(fd);
        switch (init) {
        case '\\':
            if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                return NULL;
            }
            if (u_4_8_hex(vec, fd) == NULL) {
                return NULL;
            }
            if (Dynamic_Vec_Token_get_type_token(vec) != INIT_TYPE) {
                return vec;
            }
            break;
        default:
            if (isalpha(init) || isdigit(init) || init == '_') {
                if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                    return NULL;
                }
            } else {   
                if (is_key(vec)) {
                    Dynamic_Vec_Token_set_type_token(vec, KEY);
                } else {
                    Dynamic_Vec_Token_set_type_token(vec, IDENT); 
                }  
                if (init != EOF) {
                    fseek(fd, SH_ONE_BK, SEEK_CUR);
                }
                return vec;
            }   
        }
    }       
}

static Dynamic_Vec_Token *
comment_new_token(Dynamic_Vec_Token *vec, FILE *fd)
{
    int init = 0;
    while (TRUE) {
        init = fgetc(fd);
        if (init != '\n') {
            if (init == EOF) {
                Dynamic_Vec_Token_set_type_token(vec, NO);
                return vec;
            }   
            if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                return NULL;
            }
            continue;
        } else {
            if(Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                return NULL;
            }
            Dynamic_Vec_Token_set_type_token(vec, COMMENT);
            return vec;
        }
    }
}   

static Dynamic_Vec_Token *
comment_old_token(Dynamic_Vec_Token *vec, FILE *fd)
{
    int init = 0;
    while (TRUE) {
        init = fgetc(fd);
        if (init != '*') {
            if (init == EOF) {
                Dynamic_Vec_Token_set_type_token(vec, NO);
                return vec;
            }   
            if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                return NULL;
            }
            continue;
        } else {
           if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                return NULL;
            }
            while (TRUE) {
                init = fgetc(fd);
                if (init == '*') {
                    if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                        return NULL;
                    }
                    continue;
                }
                if (init != '/') {
                    if (init == EOF) {
                        Dynamic_Vec_Token_set_type_token(vec, NO);
                        return vec;
                    }       
                    if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                        return NULL;
                    }    
                    break;
                } else {
                    if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                        return NULL;
                    }
                    Dynamic_Vec_Token_set_type_token(vec, COMMENT);
                    return vec;
                }
            }
            continue;
        }             
    }
}

static Dynamic_Vec_Token *
punct_token(Dynamic_Vec_Token *vec, FILE *fd)
{
    int init = 0;
    while (TRUE) {
        init = fgetc(fd);
        if (memchr(punctuators, init, SIZE_SET_PUNCT) != NULL) {
            if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                return NULL;
            }
        } else {
            Dynamic_Vec_Token_set_type_token(vec, PUNCT);
            fseek(fd, SH_ONE_BK, SEEK_CUR);
            return vec;
        }
    }
}

Dynamic_Vec_Token *
Define_Token_define_token(Define_Token *def, Dynamic_Vec_Token *vec)
{   
    int init = 0;
    init = fgetc(def->fd);
    if (init == EOF) {
        Dynamic_Vec_Token_set_type_token(vec, EOF_RET);
        return vec;
    }
    if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
        return NULL;
    }
    if (init == 'u') {
        init = fgetc(def->fd);  
        if (init == EOF) {
            Dynamic_Vec_Token_set_type_token(vec, IDENT);
            return vec;
        }
        if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
            return NULL;
        }
        if (init == '8') {    
            init = fgetc(def->fd);
            if (init == EOF) {
                Dynamic_Vec_Token_set_type_token(vec, IDENT);
                return vec;
            }   
            if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                return NULL;
            }
            if (isalpha(init) || isdigit(init) || init == '_' || init == '\\') {
                return ident_token(vec, def->fd);
            }
            if (init == '\"') {
                return string_token(vec, def->fd);
            }
            Dynamic_Vec_Token_set_type_token(vec, IDENT);
            return vec;   
        }      
        if (isalpha(init) || isdigit(init) || init == '\\' || init == '_') {
            return ident_token(vec, def->fd);
        }
        if (init == '\'') {
            return char_token(vec, def->fd);
        }
        if (init == '\"') {
            return string_token(vec, def->fd);
        }
        fseek(def->fd, SH_ONE_BK, SEEK_CUR);
        Dynamic_Vec_Token_set_type_token(vec, IDENT);
        return vec;
    }           
    if (memchr(set_id_ch_str, init, SIZE_SET_ID_CH_STR) != NULL) {
        init = fgetc(def->fd);
        if (init == EOF) {
            Dynamic_Vec_Token_set_type_token(vec, IDENT);
            return vec;
        }
        if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
            return NULL;
        }
        if (isalpha(init) || isdigit(init) || init == '_' || init == '\\') {
            return ident_token(vec, def->fd);
        }
        if (init == '\'') {
            return char_token(vec, def->fd);
        }
        if (init == '\"') {
            return string_token(vec, def->fd);
        }
        fseek(def->fd, SH_ONE_BK, SEEK_CUR);
        Dynamic_Vec_Token_set_type_token(vec, IDENT);
        return vec;
    }
    if (isalpha(init) || init == '_' || init == '\\') {
        return ident_token(vec, def->fd);
    }
    if (isdigit(init) && (init != '0')) {
        return int_dec_token(vec, def->fd);
    }
    if (init == '0') {
        return int_oct_token(vec, def->fd);
    }
    if (init == '\'') {
        return char_token(vec, def->fd);
    }
    if (init == '\"') {
        return string_token(vec, def->fd);
    }
    if (init == '/') {
        init = fgetc(def->fd);
        if (init == EOF) {
            Dynamic_Vec_Token_set_type_token(vec, PUNCT);
            return vec;
        }
        if (init == '/') {
            if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                return NULL;
            }
            return comment_new_token(vec, def->fd);
        }  
        if (init == '*') {
            if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                return NULL;
            }
            return comment_old_token(vec, def->fd);
        } 
        fseek(def->fd, SH_ONE_BK, SEEK_CUR);
        Dynamic_Vec_Token_set_type_token(vec, PUNCT);
        return vec;
    }
    if (memchr(punctuators, init, SIZE_SET_PUNCT) != NULL) {
        return punct_token(vec, def->fd);
    }
    Dynamic_Vec_Token_set_type_token(vec, NO);
    return vec;
}   

static int
equal_sets(Dynamic_Vec_Token *vec, char *set) 
{
    int end = Dynamic_Vec_Token_get_end_token(vec);
    int data = 0;
    for (int i = 0; i < end; i++) {
        Dynamic_Vec_Token_get_sym_token(vec, i, &data);
        if(data != set[i]) {
            return FALSE;
        }
    }
    return TRUE;
}

static int
is_key(Dynamic_Vec_Token *vec) 
{
    static char uns_word[] = "unsigned";
    static char void_word[] = "void";
    static char volat_word[] = "volatile";
    static char while_word[] = "while";
    static char alas_word[] = "_Alignas";
    static char alof_word[] = "_Alignof";
    static char atom_word[] = "_Atomic";
    static char bool_word[] = "_Bool";
    static char comp_word[] = "_Complex";
    static char gen_word[] = "_Generic";
    static char imag_word[] = "_Imaginary";
    static char noret_word[] = "_Noreturn";
    static char stass_word[] = "_Static_assert";
    static char thread_word[] = "_Thread_local";

    switch (Dynamic_Vec_Token_get_end_token(vec)) {
    case SIZE_UNS:
        if (equal_sets(vec, uns_word) || equal_sets(vec, comp_word) 
                || equal_sets(vec, gen_word) || equal_sets(vec, volat_word)
                || equal_sets(vec, alas_word) || equal_sets(vec, alof_word)) {
            return TRUE;
        } else {
            return FALSE;
        }

    case SIZE_VOID:
        return equal_sets(vec, void_word);

    case SIZE_ATOM:
        return equal_sets(vec, atom_word);
 
    case SIZE_BOOL:
        return (equal_sets(vec, bool_word) || equal_sets(vec, while_word));
 
    case SIZE_IMAG:
        return equal_sets(vec, imag_word);
 
    case SIZE_NORET:
        return equal_sets(vec, noret_word);
 
    case SIZE_STASS:
        return equal_sets(vec, stass_word);
 
    case SIZE_THR:
        return equal_sets(vec, thread_word);
    
    default:
        return FALSE;       
    }
}

static Dynamic_Vec_Token *
hex_only(Dynamic_Vec_Token *vec, FILE *fd)
{
    int init = fgetc(fd);
    if (!isxdigit(init)) {
        fseek(fd, SH_ONE_BK, SEEK_CUR);
        Dynamic_Vec_Token_set_type_token(vec, NO);
        return vec;
    }
    if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
        return NULL;
    }
    Dynamic_Vec_Token_set_type_token(vec, INIT_TYPE);
    while (TRUE) {
        init = fgetc(fd);
        if (isxdigit(init)) {
            if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                return NULL;
            }
            continue;
        }
        fseek(fd, SH_ONE_BK, SEEK_CUR);
        return vec;    
    }
}    

static Dynamic_Vec_Token *
oct_less_eq_3(Dynamic_Vec_Token *vec, FILE *fd)
{
    int init = 0;
    for (int i = 0; i <= 2; i++) {
        init = fgetc(fd);
        if (isdigit(init) && init != '8' && init != '9') {
            if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                return NULL;
            }
            continue;
        } 
        if (i == 0) {
            Dynamic_Vec_Token_set_type_token(vec, NO);
        } else {
            Dynamic_Vec_Token_set_type_token(vec, INIT_TYPE);
        }
        fseek(fd, SH_ONE_BK, SEEK_CUR);
        return vec;
    }
    Dynamic_Vec_Token_set_type_token(vec, INIT_TYPE);
    return vec;
}    

static Dynamic_Vec_Token *
u_4_8_hex(Dynamic_Vec_Token *vec, FILE *fd)
{

    int init = 0;
    int counter_hex = 0;
    for (int i = 0; i <= 9; i++) {
        init = fgetc(fd);
        if (i == 0) {
            if (init == 'u' || init == 'U') {
                if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                    return NULL;
                }
                continue;
            }
            Dynamic_Vec_Token_set_type_token(vec, NO);
            fseek(fd, SH_ONE_BK, SEEK_CUR);
            return vec;
        }
        if (isxdigit(init) && i != 9) {
            counter_hex += 1;
            if (Dynamic_Vec_Token_add_to_token(vec, init) == NULL) {
                return NULL;
            }
            continue;
        } else if (counter_hex % DIV_F == 0 && counter_hex != 0) {
            Dynamic_Vec_Token_set_type_token(vec, INIT_TYPE);        
        } else {
            Dynamic_Vec_Token_set_type_token(vec, NO);
        }
        fseek(fd, SH_ONE_BK, SEEK_CUR);
        return vec;
    }
    return vec;
}
