#include "Analyzer.h"
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
 *    - "buffer" is a reference on previously initialized object of type string;
 * This function is used to define integer decimal constant like token 
 * and to put into Token;
 */
Token
Analyzer::int_dec_token(string &buffer)
{
    int init = 0;
    while (TRUE) {       
        init = fgetc(fd);
        if (isdigit(init)) {
            buffer += init;
            continue;
        } else {
            Token token(buffer, CONST_INT);
            fseek(fd, SH_ONE_BK, SEEK_CUR);   
            return token;
        }
    }        
}   

/**
 * Input parameters:
 *    - "buffer" is a reference on previously initialized object of type string;
 * This function is used to define integer octal constant like token 
 * and to put into Token;
 */
Token
Analyzer::int_oct_token(string &buffer)
{
    int init = 0;
    while (TRUE) {
        init = fgetc(fd);
        if (isdigit(init) && init != '9' && init != '8') {
            buffer += init;
            continue;
        } else {
            Token token(buffer, CONST_INT);
            fseek(fd, SH_ONE_BK, SEEK_CUR);
            return token;
        }           
    }
}   

/**
 * Input parameters:
 *    - "buffer" is a reference on previously initialized object of type string;
 * This function is used to define character constant like token 
 * and to put into Token;
 */
Token
Analyzer::char_token(string &buffer)
{   
    int init = 0;
    int state_begin = 0;    
    init = fgetc(fd);
    if (init == '\'' || init == '\n') {
        buffer += init;
        Token token(buffer, NONE);
        return token;
    }   
    if (init == EOF) {
        Token token(buffer, NONE);
        return token;
    }
    while (TRUE) {
        if (state_begin) {
            init = fgetc(fd);
        }
        state_begin++;
        switch (init) {
        case '\'':
            { 
                buffer += init;
                Token token(buffer, CONST_CHAR);
                return token;
            }
        case '\\':
            buffer += init;
            init = fgetc(fd);
            switch (init) {
            case 'U':
            case 'u':
                fseek(fd, SH_ONE_BK, SEEK_CUR);   
                if (u_4_8_hex(buffer) == false) {
                    Token token(buffer, NONE);
                    return token;
                }
                continue;
            case 'x':
                buffer += init;
                if (hex_only(buffer) == false) {
                    Token token(buffer, NONE);
                    return token;
                }
                continue;
            default:
                if (isdigit(init) && init != '8' && init != '9') {
                    fseek(fd, SH_ONE_BK, SEEK_CUR);
                    if (oct_less_eq_3(buffer) == false) {
                        Token token(buffer, NONE);
                        return token;
                    }
                    continue;
                } else if (memchr(simple_escape, init, SIZE_SET_SIM_ESC) != NULL) {
                    buffer += init;
                    continue;
                } else {
                    fseek(fd, SH_ONE_BK, SEEK_CUR);
                    Token token(buffer, NONE);
                    return token;
                }
            }
        default:
            if (init == EOF) {
                Token token(buffer, NONE);
                return token;
            }
            if (init == '\n') {
                buffer += init;
                Token token(buffer, NONE);
                return token;
            }  
            buffer += init;
            continue;  
        }
    }
}       

/**
 * Input parameters:
 *    - "buffer" is a reference on previously initialized object of type string;
 * This function is used to define string constant like token 
 * and to put into Token;
 */
Token
Analyzer::string_token(string &buffer)
{
    int init = 0;    
    while (TRUE) {
        init = fgetc(fd);
        switch (init) {
        case '\"':
            {
                buffer += init;
                Token token(buffer, CONST_STR);
                return token;
            }    
        case '\\':
            buffer += init;
            init = fgetc(fd);
            switch (init) {
            case 'U':
            case 'u':
                fseek(fd, SH_ONE_BK, SEEK_CUR);   
                if (u_4_8_hex(buffer) == false) {
                    Token token(buffer, NONE);
                    return token;
                }
                continue;
            case 'x':
                buffer += init;
                if (hex_only(buffer) == false) {
                    Token token(buffer, NONE);
                    return token;
                }
                continue;
            default:
                if (isdigit(init) && init != '8' && init != '9') {
                    fseek(fd, SH_ONE_BK, SEEK_CUR);
                    if (oct_less_eq_3(buffer) == false) {
                        Token token(buffer, NONE);
                        return token;
                    }
                    continue;
                } else if (memchr(simple_escape, init, SIZE_SET_SIM_ESC) != NULL) {
                    buffer += init;
                    continue;
                } else {
                    Token token(buffer, NONE);
                    return token;
                }
            }
        default:
            if (init == EOF) {
                Token token(buffer, NONE);
                return token;
            }
            if (init == '\n') {
                buffer += init;
                Token token(buffer, NONE);
                return token;
            }
            buffer += init;
            continue;  
        }
    }
}           

/**
 * Input parameters:
 *    - "buffer" is a reference on previously initialized object of type string;
 * This function is used to define identificator like token 
 * and to put into Token;
 */
Token
Analyzer::ident_token(string &buffer)
{ 
    int init = 0;
    while (TRUE) {
        init = fgetc(fd);
        switch (init) {
        case '\\':
            buffer += init;
            if (u_4_8_hex(buffer) == false) {
                Token token(buffer, NONE);
                return token;
            }
            break;
        default:
            TokenType type = KEY;
            if (isalpha(init) || isdigit(init) || init == '_') {
                buffer += init;
            } else {   
                if (is_key(buffer)) {
                    type = KEY;
                } else {
                    type = IDENT; 
                }  
                if (init != EOF) {
                    fseek(fd, SH_ONE_BK, SEEK_CUR);
                }
                Token token(buffer, type);
                return token;
            }   
        }
    }       
}

/**
 * Input parameters:
 *    - "buffer" is a reference on previously initialized object of type string;
 * This function is used to define comment new style like token 
 * and to put into Token;
 */
Token
Analyzer::comment_new_token(string &buffer)
{
    int init = 0;
    while (TRUE) {
        init = fgetc(fd);
        if (init != '\n') {
            if (init == EOF) {
                Token token(buffer, NONE);
                return token;
            }   
            buffer += init;
            continue;
        } else {
            buffer += init;
            Token token(buffer, COMMENT);
            return token;
        }
    }
}   

/**
 * Input parameters:
 *    - "buffer" is a reference on previously initialized object of type string;
 * This function is used to define comment old style like token 
 * and to put into Token;
 */
Token
Analyzer::comment_old_token(string &buffer)
{
    int init = 0;
    while (TRUE) {
        init = fgetc(fd);
        if (init != '*') {
            if (init == EOF) {
                Token token(buffer, NONE);
                return token;
            }   
            buffer += init;
            continue;
        } else {
            buffer += init;
            while (TRUE) {
                init = fgetc(fd);
                if (init == '*') {
                    buffer += init;
                    continue;
                }
                if (init != '/') {
                    if (init == EOF) {
                        Token token(buffer, NONE);
                        return token;
                    }       
                    buffer += init;
                    break;
                } else {
                    buffer += init;
                    Token token(buffer, COMMENT);
                    return token;
                }
            }
            continue;
        }             
    }
}

/**
 * Input parameters:
 *    - "buffer" is a reference on previously initialized object of type string;
 * This function is used to define punctuator like token 
 * and to put into Token;
 */
Token
Analyzer::punct_token(string &buffer)
{
    int init = 0;
    while (TRUE) {
        init = fgetc(fd);
        if (memchr(punctuators, init, SIZE_SET_PUNCT) != NULL) {
            buffer += init;
        } else {
            Token token(buffer, PUNCT);
            fseek(fd, SH_ONE_BK, SEEK_CUR);
            return token;
        }
    }
}

Token
Analyzer::get_token()
{   
    string buffer;
    int init = 0;
    init = fgetc(fd);
    if (init == EOF) {
        Token token(buffer, EOF_RET);
        return token;
    }
    buffer += init;
    if (init == 'u') {
        init = fgetc(fd);  
        if (init == EOF) {
            Token token(buffer, IDENT);
            return token;
        }
        buffer += init;
        if (init == '8') {    
            init = fgetc(fd);
            if (init == EOF) {
                Token token(buffer, IDENT);
                return token;
            }   
            buffer += init;
            if (isalpha(init) || isdigit(init) || init == '_' || init == '\\') {
                return ident_token(buffer);
            }
            if (init == '\"') {
                return string_token(buffer);
            }
            Token token(buffer, IDENT);
            return token;   
        }      
        if (isalpha(init) || isdigit(init) || init == '\\' || init == '_') {
            return ident_token(buffer);
        }
        if (init == '\'') {
            return char_token(buffer);
        }
        if (init == '\"') {
            return string_token(buffer);
        }
        fseek(fd, SH_ONE_BK, SEEK_CUR);
        Token token(buffer, IDENT);
        return token;
    }           
    if (memchr(set_id_ch_str, init, SIZE_SET_ID_CH_STR) != NULL) {
        init = fgetc(fd);
        if (init == EOF) {
            Token token(buffer, IDENT);
            return token;
        }
        buffer += init;
        if (isalpha(init) || isdigit(init) || init == '_' || init == '\\') {
            return ident_token(buffer);
        }
        if (init == '\'') {
            return char_token(buffer);
        }
        if (init == '\"') {
            return string_token(buffer);
        }
        fseek(fd, SH_ONE_BK, SEEK_CUR);
        Token token(buffer, IDENT);
        return token;
    }
    if (isalpha(init) || init == '_' || init == '\\') {
        return ident_token(buffer);
    }
    if (isdigit(init) && (init != '0')) {
        return int_dec_token(buffer);
    }
    if (init == '0') {
        return int_oct_token(buffer);
    }
    if (init == '\'') {
        return char_token(buffer);
    }
    if (init == '\"') {
        return string_token(buffer);
    }
    if (init == '/') {
        init = fgetc(fd);
        if (init == EOF) {
            Token token(buffer, PUNCT);
            return token;
        }
        if (init == '/') {
            buffer += init;
            return comment_new_token(buffer);
        }  
        if (init == '*') {
            buffer += init;
            return comment_old_token(buffer);
        } 
        fseek(fd, SH_ONE_BK, SEEK_CUR);
        Token token(buffer, PUNCT);
        return token;
    }
    if (memchr(punctuators, init, SIZE_SET_PUNCT) != NULL) {
        return punct_token(buffer);
    }
    Token token(buffer, NONE);
    return token;
}   

/**
 * Input parameters:
 *    - "buffer" is a reference on previously initialized object of type string;
 * Output parameters:
 *    - returns true if buffer is equal to key token;
 *    - returns false if buffer is not equal to key token;
 * Description: 
 *    This function check if input token is a key token;
 */
bool
Analyzer::is_key(string &buffer) 
{
    static string uns_word("unsigned");
    static string void_word("void");
    static string volat_word("volatile");
    static string while_word("while");
    static string alas_word("_Alignas");
    static string alof_word("_Alignof");
    static string atom_word("_Atomic");
    static string bool_word("_Bool");
    static string comp_word("_Complex");
    static string gen_word("_Generic");
    static string imag_word("_Imaginary");
    static string noret_word("_Noreturn");
    static string stass_word("_Static_assert");
    static string thread_word("_Thread_local");

    switch (buffer.size()) {
    case SIZE_UNS:
        if (buffer == uns_word || buffer == comp_word 
                || buffer == gen_word || buffer == volat_word
                || buffer == alas_word || buffer == alof_word) {
            return true;
        } else {
            return false;
        }

    case SIZE_VOID:
        return buffer == void_word;

    case SIZE_ATOM:
        return buffer == atom_word;
 
    case SIZE_BOOL:
        return (buffer == bool_word || buffer == while_word);
 
    case SIZE_IMAG:
        return buffer == imag_word;
 
    case SIZE_NORET:
        return buffer == noret_word;
 
    case SIZE_STASS:
        return buffer == stass_word;
 
    case SIZE_THR:
        return buffer == thread_word;
    
    default:
        return false;       
    }
}

/**
 * Input parameters:
 *    - "buffer" is a reference on previously initialized object of type string;
 * Description:
 *    This function returns true if token is regular and false if it is not.
 */
bool
Analyzer::hex_only(string &buffer)
{
    int init = fgetc(fd);
    if (!isxdigit(init)) {
        fseek(fd, SH_ONE_BK, SEEK_CUR);
        return false;
    }
    buffer += init;
    while (TRUE) {
        init = fgetc(fd);
        if (isxdigit(init)) {
            buffer += init;
            continue;
        }
        fseek(fd, SH_ONE_BK, SEEK_CUR);
        return true;    
    }
}    

/**
 * Input parameters:
 *    - "buffer" is a reference on previously initialized object of type string;
 * Description:
 *    This function returns true if token is regular, false in contrast;
 *    It pulls only 0 < x <= 3 octuple digits into buffer;
 */
bool
Analyzer::oct_less_eq_3(string &buffer)
{
    int init = 0;
    for (int i = 0; i <= 2; i++) {
        bool flag = true;
        init = fgetc(fd);
        if (isdigit(init) && init != '8' && init != '9') {
            buffer += init;
            continue;
        } 
        if (i == 0) {
            flag = false;
        } else {
            flag = true;
        }
        fseek(fd, SH_ONE_BK, SEEK_CUR);
        return flag;
    }
    return true;
}    

/**
 * Input parameters:
 *    - "token" is a reference on previously initialized object of type Token;
 * Description:
 *    This function sets type of token: INIT_TYPE if token is regular, NO in contrast;
 *    It pulls only 4 or 8 heximal digits into token else token type=NO;
 */
bool
Analyzer::u_4_8_hex(string &buffer)
{
    bool flag = true;
    int init = 0;
    int counter_hex = 0;
    for (int i = 0; i <= 9; i++) {
        init = fgetc(fd);
        if (i == 0) {
            if (init == 'u' || init == 'U') {
                buffer += init;
                continue;
            }
            fseek(fd, SH_ONE_BK, SEEK_CUR);
            return false;
        }
        if (isxdigit(init) && i != 9) {
            counter_hex += 1;
            buffer += init;
            continue;
        } else if (counter_hex % DIV_F == 0 && counter_hex != 0) {
            flag = true;        
        } else {
            flag = false;
        }
        fseek(fd, SH_ONE_BK, SEEK_CUR);
        return flag;
    }
    return true;
}

Analyzer::Analyzer(FILE *fp)
{ 
    fd = fp;
}

