#include "Define_Token.h"
#include <cstring>
#include <cctype>

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
 *    - "token" is a reference on previously initialized object of type Token;
 * This function is used to define integer decimal constant like token 
 * and to put into Token;
 */
void
Define_Token::int_dec_token(Token &token)
{
    int init = 0;
    while (TRUE) {       
        init = fgetc(fd);
        if (isdigit(init)) {
            token.add_to(init);
            continue;
        } else {
            token.set_type(CONST_INT);
            fseek(fd, SH_ONE_BK, SEEK_CUR);   
            return;
        }
    }        
}   

/**
 * Input parameters:
 *    - "token" is a reference on previously initialized object of type Token;
 * This function is used to define integer octal constant like token 
 * and to put into Token;
 */
void
Define_Token::int_oct_token(Token &token)
{
    int init = 0;
    while (TRUE) {
        init = fgetc(fd);
        if (isdigit(init) && init != '9' && init != '8') {
            token.add_to(init);
            continue;
        } else {
            token.set_type(CONST_INT);
            fseek(fd, SH_ONE_BK, SEEK_CUR);
            return;
        }           
    }
}   

/**
 * Input parameters:
 *    - "token" is a reference on previously initialized object of type Token;
 * This function is used to define character constant like token 
 * and to put into Token;
 */
void
Define_Token::char_token(Token &token)
{   
    int init = 0;
    int state_begin = 0;    
    init = fgetc(fd);
    if (init == '\'' || init == '\n') {
        token.add_to(init);
        token.set_type(NO);
        return;
    }   
    if (init == EOF) {
        token.set_type(NO);
        return;
    }
    while (TRUE) {
        if (state_begin) {
            init = fgetc(fd);
        }
        state_begin++;
        switch (init) {
        case '\'':
            token.add_to(init);
            token.set_type(CONST_CHAR);
            return;
        case '\\':
            token.add_to(init);
            init = fgetc(fd);
            switch (init) {
            case 'U':
            case 'u':
                fseek(fd, SH_ONE_BK, SEEK_CUR);   
                u_4_8_hex(token);
                if (token.get_type() != INIT_TYPE) {
                    return;
                }
                continue;
            case 'x':
                token.add_to(init);
                hex_only(token);
                if (token.get_type() != INIT_TYPE) {
                    return;
                }
                continue;
            default:
                if (isdigit(init) && init != '8' && init != '9') {
                    fseek(fd, SH_ONE_BK, SEEK_CUR);
                    oct_less_eq_3(token);
                    if (token.get_type() != INIT_TYPE) {
                        return;
                    }
                    continue;
                } else if (memchr(simple_escape, init, SIZE_SET_SIM_ESC) != NULL) {
                    token.add_to(init);
                    continue;
                } else {
                    fseek(fd, SH_ONE_BK, SEEK_CUR);
                    token.set_type(NO);
                    return;
                }
            }
        default:
            if (init == EOF) {
                token.set_type(NO);
                return;
            }
            if (init == '\n') {
                token.add_to(init);
                token.set_type(NO);
                return;
            }  
            token.add_to(init);
            continue;  
        }
    }
}       

/**
 * Input parameters:
 *    - "token" is a reference on previously initialized object of type Token;
 * This function is used to define string constant like token 
 * and to put into Token;
 */
void
Define_Token::string_token(Token &token)
{
    int init = 0;    
    while (TRUE) {
        init = fgetc(fd);
        switch (init) {
        case '\"':
            token.add_to(init);
            token.set_type(CONST_STR);
            return;
        case '\\':
            token.add_to(init);
            init = fgetc(fd);
            switch (init) {
            case 'U':
            case 'u':
                fseek(fd, SH_ONE_BK, SEEK_CUR);   
                u_4_8_hex(token);
                if (token.get_type() != INIT_TYPE) {
                    return;
                }
                continue;
            case 'x':
                token.add_to(init);
                hex_only(token);
                if (token.get_type() != INIT_TYPE) {
                    return;
                }
                continue;
            default:
                if (isdigit(init) && init != '8' && init != '9') {
                    fseek(fd, SH_ONE_BK, SEEK_CUR);
                    oct_less_eq_3(token);
                    if (token.get_type() != INIT_TYPE) {
                        return;
                    }
                    continue;
                } else if (memchr(simple_escape, init, SIZE_SET_SIM_ESC) != NULL) {
                    token.add_to(init);
                    continue;
                } else {
                    token.set_type(NO);
                    return;
                }
            }
        default:
            if (init == EOF) {
                token.set_type(NO);
                return;
            }
            if (init == '\n') {
                token.add_to(init);
                token.set_type(NO);
                return;
            }
            token.add_to(init);
            continue;  
        }
    }
}           

/**
 * Input parameters:
 *    - "token" is a reference on previously initialized object of type Token;
 * This function is used to define identificator like token 
 * and to put into Token;
 */
void
Define_Token::ident_token(Token &token)
{ 
    int init = 0;
    while (TRUE) {
        init = fgetc(fd);
        switch (init) {
        case '\\':
            token.add_to(init);
            u_4_8_hex(token);
            if (token.get_type() != INIT_TYPE) {
                return;
            }
            break;
        default:
            if (isalpha(init) || isdigit(init) || init == '_') {
                token.add_to(init);
            } else {   
                if (is_key(token)) {
                    token.set_type(KEY);
                } else {
                    token.set_type(IDENT); 
                }  
                if (init != EOF) {
                    fseek(fd, SH_ONE_BK, SEEK_CUR);
                }
                return;
            }   
        }
    }       
}

/**
 * Input parameters:
 *    - "token" is a reference on previously initialized object of type Token;
 * This function is used to define comment new style like token 
 * and to put into Token;
 */
void
Define_Token::comment_new_token(Token &token)
{
    int init = 0;
    while (TRUE) {
        init = fgetc(fd);
        if (init != '\n') {
            if (init == EOF) {
                token.set_type(NO);
                return;
            }   
            token.add_to(init);
            continue;
        } else {
            token.add_to(init);
            token.set_type(COMMENT);
            return;
        }
    }
}   

/**
 * Input parameters:
 *    - "token" is a reference on previously initialized object of type Token;
 * This function is used to define comment old style like token 
 * and to put into Token;
 */
void
Define_Token::comment_old_token(Token &token)
{
    int init = 0;
    while (TRUE) {
        init = fgetc(fd);
        if (init != '*') {
            if (init == EOF) {
                token.set_type(NO);
                return;
            }   
            token.add_to(init);
            continue;
        } else {
            token.add_to(init);
            while (TRUE) {
                init = fgetc(fd);
                if (init == '*') {
                    token.add_to(init);
                    continue;
                }
                if (init != '/') {
                    if (init == EOF) {
                        token.set_type(NO);
                        return;
                    }       
                    token.add_to(init);
                    break;
                } else {
                    token.add_to(init);
                    token.set_type(COMMENT);
                    return;
                }
            }
            continue;
        }             
    }
}

/**
 * Input parameters:
 *    - "token" is a reference on previously initialized object of type Token;
 * This function is used to define punctuator like token 
 * and to put into Token;
 */
void
Define_Token::punct_token(Token &token)
{
    int init = 0;
    while (TRUE) {
        init = fgetc(fd);
        if (memchr(punctuators, init, SIZE_SET_PUNCT) != NULL) {
            token.add_to(init);
        } else {
            token.set_type(PUNCT);
            fseek(fd, SH_ONE_BK, SEEK_CUR);
            return;
        }
    }
}

void
Define_Token::define_token(Token &token)
{   
    int init = 0;
    init = fgetc(fd);
    if (init == EOF) {
        token.set_type(EOF_RET);
        return;
    }
    token.add_to(init);
    if (init == 'u') {
        init = fgetc(fd);  
        if (init == EOF) {
            token.set_type(IDENT);
            return;
        }
        token.add_to(init);
        if (init == '8') {    
            init = fgetc(fd);
            if (init == EOF) {
                token.set_type(IDENT);
                return;
            }   
            token.add_to(init);
            if (isalpha(init) || isdigit(init) || init == '_' || init == '\\') {
                ident_token(token);
                return;
            }
            if (init == '\"') {
                string_token(token);
                return;
            }
            token.set_type(IDENT);
            return;   
        }      
        if (isalpha(init) || isdigit(init) || init == '\\' || init == '_') {
            ident_token(token);
            return;
        }
        if (init == '\'') {
            char_token(token);
            return;
        }
        if (init == '\"') {
            string_token(token);
            return;
        }
        fseek(fd, SH_ONE_BK, SEEK_CUR);
        token.set_type(IDENT);
        return;
    }           
    if (memchr(set_id_ch_str, init, SIZE_SET_ID_CH_STR) != NULL) {
        init = fgetc(fd);
        if (init == EOF) {
            token.set_type(IDENT);
            return;
        }
        token.add_to(init);
        if (isalpha(init) || isdigit(init) || init == '_' || init == '\\') {
            ident_token(token);
            return;
        }
        if (init == '\'') {
            char_token(token);
            return;
        }
        if (init == '\"') {
            string_token(token);
            return;
        }
        fseek(fd, SH_ONE_BK, SEEK_CUR);
        token.set_type(IDENT);
        return;
    }
    if (isalpha(init) || init == '_' || init == '\\') {
        ident_token(token);
        return;
    }
    if (isdigit(init) && (init != '0')) {
        int_dec_token(token);
        return;
    }
    if (init == '0') {
        int_oct_token(token);
        return;
    }
    if (init == '\'') {
        char_token(token);
        return;
    }
    if (init == '\"') {
        string_token(token);
        return;
    }
    if (init == '/') {
        init = fgetc(fd);
        if (init == EOF) {
            token.set_type(PUNCT);
            return;
        }
        if (init == '/') {
            token.add_to(init);
            comment_new_token(token);
            return;
        }  
        if (init == '*') {
            token.add_to(init);
            comment_old_token(token);
            return;
        } 
        fseek(fd, SH_ONE_BK, SEEK_CUR);
        token.set_type(PUNCT);
        return;
    }
    if (memchr(punctuators, init, SIZE_SET_PUNCT) != NULL) {
        punct_token(token);
        return;
    }
    token.set_type(NO);
    return;
}   

/**
 * Input parameters:
 *    - "token" is a reference on previously initialized object of type Token;
 *    - "set" is a pointer on set that is of the same size as token;
 * Output parameters:
 *    - returns 1 if sets are equal;
 *    - returns 0 if sets are not equal;
 * Description: 
 *    This function compares two sets of equal size;
 */
int
Define_Token::equal_sets(Token &token, char *set) 
{
    int end = token.get_end();
    for (int i = 0; i < end; i++) {
        if(token.get_symbol(i) != set[i]) {
            return FALSE;
        }
    }
    return TRUE;
}

/**
 * Input parameters:
 *    - "token" is a reference on previously initialized object of type Token;
 * Output parameters:
 *    - returns 1 if token is equal to key token;
 *    - returns 0 if token is not equal to key token;
 * Description: 
 *    This function check if input token is a key token;
 */
int
Define_Token::is_key(Token &token) 
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

    switch (token.get_end()) {
    case SIZE_UNS:
        if (equal_sets(token, uns_word) || equal_sets(token, comp_word) 
                || equal_sets(token, gen_word) || equal_sets(token, volat_word)
                || equal_sets(token, alas_word) || equal_sets(token, alof_word)) {
            return TRUE;
        } else {
            return FALSE;
        }

    case SIZE_VOID:
        return equal_sets(token, void_word);

    case SIZE_ATOM:
        return equal_sets(token, atom_word);
 
    case SIZE_BOOL:
        return (equal_sets(token, bool_word) || equal_sets(token, while_word));
 
    case SIZE_IMAG:
        return equal_sets(token, imag_word);
 
    case SIZE_NORET:
        return equal_sets(token, noret_word);
 
    case SIZE_STASS:
        return equal_sets(token, stass_word);
 
    case SIZE_THR:
        return equal_sets(token, thread_word);
    
    default:
        return FALSE;       
    }
}

/**
 * Input parameters:
 *    - "token" is a reference on previously initialized object of type Token;
 * Description:
 *    This function sets type of token: INIT_TYPE if token is regular,
 *    NO in contrast;
 *    It pulls only heximal digits into token else token type=NO;
 */
void
Define_Token::hex_only(Token &token)
{
    int init = fgetc(fd);
    if (!isxdigit(init)) {
        fseek(fd, SH_ONE_BK, SEEK_CUR);
        token.set_type(NO);
        return;
    }
    token.add_to(init);
    token.set_type(INIT_TYPE);
    while (TRUE) {
        init = fgetc(fd);
        if (isxdigit(init)) {
            token.add_to(init);
            continue;
        }
        fseek(fd, SH_ONE_BK, SEEK_CUR);
        return;    
    }
}    

/**
 * Input parameters:
 *    - "token" is a reference on previously initialized object of type Token;
 * Description:
 *    This function sets type of token: INIT_TYPE if token is regular, NO in contrast;
 *    It pulls only 0 < x <= 3 octuple digits into token else token type=NO;
 */
void
Define_Token::oct_less_eq_3(Token &token)
{
    int init = 0;
    for (int i = 0; i <= 2; i++) {
        init = fgetc(fd);
        if (isdigit(init) && init != '8' && init != '9') {
            token.add_to(init);
            continue;
        } 
        if (i == 0) {
            token.set_type(NO);
        } else {
            token.set_type(INIT_TYPE);
        }
        fseek(fd, SH_ONE_BK, SEEK_CUR);
        return;
    }
    token.set_type(INIT_TYPE);
    return;
}    

/**
 * Input parameters:
 *    - "token" is a reference on previously initialized object of type Token;
 * Description:
 *    This function sets type of token: INIT_TYPE if token is regular, NO in contrast;
 *    It pulls only 4 or 8 heximal digits into token else token type=NO;
 */
void
Define_Token::u_4_8_hex(Token &token)
{

    int init = 0;
    int counter_hex = 0;
    for (int i = 0; i <= 9; i++) {
        init = fgetc(fd);
        if (i == 0) {
            if (init == 'u' || init == 'U') {
                token.add_to(init);
                continue;
            }
            token.set_type(NO);
            fseek(fd, SH_ONE_BK, SEEK_CUR);
            return;
        }
        if (isxdigit(init) && i != 9) {
            counter_hex += 1;
            token.add_to(init);
            continue;
        } else if (counter_hex % DIV_F == 0 && counter_hex != 0) {
            token.set_type(INIT_TYPE);        
        } else {
            token.set_type(NO);
        }
        fseek(fd, SH_ONE_BK, SEEK_CUR);
        return;
    }
    return;
}

Define_Token::Define_Token(FILE *fp)
{ 
    fd = fp;
}

Define_Token::~Define_Token()
{
    
}
