#include "analyzer.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
 * This function, paint_return_analyzer, allows you to print an array=buffer up to 
 * position(included) in different strictly known colours, free an array=buffer, 
 * and move file pointer from current state to back steps.
 * Input parameters:
 *     - "fd" is of FILE* type (stdio.h) and it is a pointer on OPENED previously file;
 *     - "buffer" is a dynamic array created previously;
 *     - "position" is an index in buffer up to that(included) we want our function to 
 *       interact with buffer; 
 *     - "paint" is a reserved constant to be interpreted as colour;
 *     - "back" is a number of steps to shift from current position in file via fd;
 * Important: this function supposes that it is used in a regular way;
 */ 
static void paint_return_analyzer(FILE *fd, int *buffer, int position, char paint, int back);

/**
 * This function, int_dec_token, allows you to enter some(undefined) characters from opened
 * file via fd into dynamic buffer from position up to character that cannot be 
 * in decimal constant, print this buffer in orange colour if it`s regular, and no colour if
 * it is not, free buffer, shift file pointer.
 * Important: this function is not supposed to be used out of "analyzer" function;
 * Input parameters:
 *     - "buffer" is a dynamic array in which characters from file are stored;
 *     - "size_buf" is a size of "buffer";
 *     - "position" is an index in buffer from that we want our function to 
 *       interact with buffer;
 *     - "fd" is of FILE* type (stdio.h) and it is a pointer on OPENED previously file;
 * Output parameters:
 *     - function returns 0 if everything is fine;
 *     - function returns -1 if we have a problem with memory(dynamic memory is full);
 * Important: this function supposes that it is used in a regular way;
 */
static int int_dec_token(int *buffer, int size_buf, int position, FILE *fd);

/**
 * This function, int_oct_token, allows you to enter some(undefined) characters from opened 
 * file via fd into dynamic buffer from position up to character that cannot be 
 * in octuple constant, print this buffer in orange colour if it`s regular, and no colour if
 * it is not, free buffer, shift file pointer.
 * All the next requirements and descriptions are the same as in "int_dec_token"
 */ 
static int int_oct_token(int *buffer, int size_buf, int position, FILE *fd);

/**
 * This function, char_token, allows you to enter some(undefined) characters from opened
 * file via fd into dynamic buffer from position up to character that cannot be
 * in char constant, print this buffer in yellow colour if it`s regular, and no colour if
 * it is not, free buffer, shift file pointer.
 * All the next requirements and descriptions are the same as in "int_dec_token".
 */ 
static int char_token(int *buffer, int size_buf, int position, FILE *fd);

/**
 * This function, string_token, allows you to enter some(undefined) characters from opened
 * file via fd into dynamic buffer from position up to character that cannot be
 * in string constant, print this buffer in green colour if it`s regular, and no colour if
 * it is not, free buffer, shift file pointer.
 * All the next requirements and descriptions are the same as in "int_dec_token".
 */ 
static int string_token(int *buffer, int size_buf, int position, FILE *fd);

/**
 * This function, equal_sets, allows you to compare two arrays=buf=set up to index=position.
 * Output parameters:
 *     - function returns 1 if sets are equal;
 *     - function returns 0 if sets are not equal;
 */
static int equal_sets(int *buffer, int pos_buf_set, char *set);

/**
 * This function, is_key, allows you realize whether buffer=array is a key token in C.
 * Output parameters:
 *     - function returns 1 if buffer is equal to key token;
 *     - function returns 0 if buffer is not equal key token;
 * Important: this function is not supposed to be used out of "analyzer" function.
 */ 
static int is_key(int *buffer, int position);

/**
 * This function, ident_token, allows you to enter some(undefined) characters from opened
 * file via fd into dynamic buffer from position up to character that cannot be
 * in identifier, print this buffer in pink colour if it`s regular, and no colour if
 * it is not, free buffer, shift file pointer.
 * All the next requirements and descriptions are the same as in "int_dec_token".
 */ 
static int ident_token(int *buffer, int size_buf, int position, FILE *fd);

/**
 * This function, comment_new_token, allows you to enter some(undefined) characters from opened
 * file via fd into dynamic buffer from position up to character that cannot be
 * in comment, print this buffer in brown colour if it`s regular, and no colour if
 * it is not, free buffer, shift file pointer.
 * All the next requirements and descriptions are the same as in "int_dec_token".
 */ 
static int comment_new_token(int *buffer, int size_buf, int position, FILE *fd);

/**
 * This function, comment_old_token, allows you to enter some(undefined) characters from opened
 * file via fd into dynamic buffer from position up to character that cannot be
 * in comment, print this buffer in brown colour if it`s regular, and no colour if
 * it is not, free buffer, shift file pointer.
 * All the next requirements and descriptions are the same as in "int_dec_token".
 */ 
static int comment_old_token(int *buffer, int size_buf, int position, FILE *fd);

/**
 * This function, out_buf, allows you to print the array=buffer to stdout 
 * up to position(included). 
 */ 
static void out_buf(int *buffer, int position);

/**
 * This function, out_buf_p, allows you to print the array=buffer to stdout
 * up to position(included) in colour defined by paint.
 */ 
static void out_buf_p(int *buffer, int position, char paint);

/**
 * This function, print_buf_def_color, helps out_buf_p to print buffer 
 * in defined color.
 */ 
static void print_buf_def_color(int *buffer, int position, char *paint);

/**
 * This function, check_give_memory, is used to give memory and check special 
 * conditions of that.
 * Input parameters:
 *     - buffer is an array we can broaden;
 *     - position is a index that notices about end of buffer;
 *     - paint is a string presenting color;
 * Output parameters:
 *     - function returns NULL if it could not give memory;
 *     - function returns number != 0 if buffer was broaden up to 2 times;
 */
static int* check_give_memory(int *buffer, int *size_buf, int position);

/**
 * This function, inc_pos_read_to_buf, increases position, and reads from opened
 * file one character.
 */ 
void inc_pos_read_to_buf(int *buffer, int *position, FILE *fd);

// These constants reflect requrements of design
enum { BUF_INIT = 1024, TRUE = 1, FALSE = 0, SIZE_SET_ID_CH_STR = 2, 
	SIZE_SET_PUNCT = 13, SIZE_SET_SIM_ESC = 11, SIZE_UCN = 9 };

// These constants reflect requrements of design
enum { ID_CH_STR = 'u', ZERO = '0', DOWN = '_' };

// These constants reflect colours of tokens
enum { IDENT_PAINT = 'i', NO_PAINT = 'n', PUNCT_PAINT = 'p',
       	KEY_PAINT = 'k', CONST_INT_PAINT = 'd', CONST_CHAR_PAINT = 'c', 
	CONST_STR_PAINT = 's', COMMENT_PAINT = '/' };

// These constants reflect sizes of key words
enum { ONE_LETTER = 1, TWO_LETTERS = 2, SIZE_UNS = 8, SIZE_VOID = 4,
        SIZE_ATOM = 7, SIZE_BOOL = 5, SIZE_COMPL = 8, SIZE_GEN = 8,
        SIZE_IMAG = 10, SIZE_NORET = 9, SIZE_STASS = 14, SIZE_THR = 13,
        SIZE_WHILE = 5, SIZE_VOLAT = 8, SIZE_ALIGNAS = 8, SIZE_ALIGNOF = 8,
	POS_TO_SIZE = 1 };

// These constants reflect requrements of design
enum { SH_ONE_BK = -1, MUL_TWO = 2, SH_TWO_BK = -2, DIV_F = 4 };

static char punctuators[] = { '+', '-', '&', '*', '~', '!', '/', '%', '<', '>', '^', '|', '=' };
static char set_id_ch_str[] = { 'L', 'U' };
static char simple_escape[] = { '\'', '\"', '?', '\\', 'a', 'b', 'f', 'n', 'r', 't', 'v' };

static void paint_return_analyzer(FILE *fd, int *buffer, int position, char paint, int back)
{
    out_buf_p(buffer, position, paint);
    free(buffer);
    fseek(fd, back, SEEK_CUR);
    return;
}

static int* check_give_memory(int *buffer, int *size_buf, int position)
{
    if (position >= (*size_buf + SH_ONE_BK)) {
        *size_buf = *size_buf * MUL_TWO;
	    buffer = realloc(buffer, *size_buf * sizeof(*buffer));
    }
    return buffer;
}	

void inc_pos_read_to_buf(int *buffer, int *position, FILE *fd)
{
    *position = *position + 1;
    buffer[*position] = fgetc(fd);
}	

static int int_dec_token(int *buffer, int size_buf, int position, FILE *fd) 
{
    while (TRUE) {	     
        if ((buffer = check_give_memory(buffer, &size_buf, position)) == NULL) {
	        return -1;
	    }
	    inc_pos_read_to_buf(buffer, &position, fd);
        if (isdigit(buffer[position])) {
	        continue;
	    } else {
	        paint_return_analyzer(fd, buffer, position + SH_ONE_BK, CONST_INT_PAINT, SH_ONE_BK);
            break;
	    }
    }	
    return 0;     
}	

static int int_oct_token(int *buffer, int size_buf, int position, FILE *fd)
{
    while (TRUE) {
 	    if ((buffer = check_give_memory(buffer, &size_buf, position)) == NULL) {
	        return -1;
	    }
	    inc_pos_read_to_buf(buffer, &position, fd);
        if (isdigit(buffer[position]) && buffer[position] != '9' && buffer[position] != '8') {
	        continue;
	    } else {
	        paint_return_analyzer(fd, buffer, position + SH_ONE_BK, CONST_INT_PAINT, SH_ONE_BK);
	        break;
	    }      	    
    }
    return 0;
}	

static int char_token(int *buffer, int size_buf, int position, FILE *fd)
{   
    int state_begin = 0;	
    int counter_hex = 0;
    if ((buffer = check_give_memory(buffer, &size_buf, position)) == NULL) {
        return -1;
    }	
    inc_pos_read_to_buf(buffer, &position, fd);
    if (buffer[position] == '\'') {
	    paint_return_analyzer(fd, buffer, position, NO_PAINT, 0);
	    return 0;
    }	
    if (buffer[position] == EOF) {
	    paint_return_analyzer(fd, buffer, position + SH_ONE_BK, NO_PAINT, 0);
	    return 0;
    }
    while (TRUE) {
        if (state_begin) {
	        if ((buffer = check_give_memory(buffer, &size_buf, position)) == NULL) {
                return -1;
    	    }
            inc_pos_read_to_buf(buffer, &position, fd);
	    }
	    state_begin++;
	    switch (buffer[position]) {
	    case '\'':
	        paint_return_analyzer(fd, buffer, position, CONST_CHAR_PAINT, 0);
            return 0;  	
        case '\\':
	        while (TRUE) {
		        int flag_x = 0;    
		        int flag_u = 0;
                if ((buffer = check_give_memory(buffer, &size_buf, position)) == NULL) {
                    return -1;
                }
                inc_pos_read_to_buf(buffer, &position, fd);
	            switch (buffer[position]) {
                case 'U':
		        case 'u':
              	    counter_hex = 0;    
	                while (TRUE) {
                        if ((buffer = check_give_memory(buffer, &size_buf, position)) == NULL) {
                            return -1;
                        }
		                inc_pos_read_to_buf(buffer, &position, fd);
			            if (buffer[position] == EOF) {
			                paint_return_analyzer(fd, buffer, position + SH_ONE_BK, NO_PAINT, 0);
			                return 0;
			            }
                        if (isxdigit(buffer[position])) {
		                    counter_hex += 1;
			                continue;
		                } else if (counter_hex % DIV_F == 0 && counter_hex != 0) {
			                switch (buffer[position]) {
		                    case '\'':
                                paint_return_analyzer(fd, buffer, position, CONST_CHAR_PAINT, 0);
				                return 0;
                            case '\\':
				                flag_u = 1;
				                break;
			                default: 
			                    break;
			                }	
		                } else {
		                    paint_return_analyzer(fd, buffer, position + SH_ONE_BK, NO_PAINT, SH_ONE_BK);
		                    return 0;
		                }
			            break;
		            }
	                break;
		        case 'x':
                    if ((buffer = check_give_memory(buffer, &size_buf, position)) == NULL) {
                        return -1;
                    }
                    inc_pos_read_to_buf(buffer, &position, fd);
		            if (buffer[position] == EOF) {
		                paint_return_analyzer(fd, buffer, position + SH_ONE_BK, NO_PAINT, 0);
                        return 0;
		            }
	                if (isxdigit(buffer[position])) {
		                while (TRUE) {
                            if ((buffer = check_give_memory(buffer, &size_buf, position)) == NULL) {
                                return -1;
                            }
                            inc_pos_read_to_buf(buffer, &position, fd);
	                        switch (buffer[position]) {
			                case '\'': 
			                    paint_return_analyzer(fd, buffer, position, CONST_CHAR_PAINT, 0);
                                return 0;
			                case '\\':
				                flag_x = 1;
                                break;
			                case EOF:
			                    paint_return_analyzer(fd, buffer, position + SH_ONE_BK, NO_PAINT, 0);	
                                return 0;
			                default:
				                if (isxdigit(buffer[position])) {
				                    continue;
				                }
				                break;
			                }
			                break;
			            }
		            } else {
		                paint_return_analyzer(fd, buffer, position + SH_ONE_BK, NO_PAINT, SH_ONE_BK);
			            return 0;
		            }
                    break;
		        case EOF:
		            paint_return_analyzer(fd, buffer, position + SH_ONE_BK, NO_PAINT, 0);
		            return 0;    
		        default:
		            if (isdigit(buffer[position]) && buffer[position] != '9' && buffer[position] != '8') {
			            int flag = 0;	
	              	    for (int i = 0; i <= 2; i++) {
                            if ((buffer = check_give_memory(buffer, &size_buf, position)) == NULL) {
                                return -1;
                            }
                            inc_pos_read_to_buf(buffer, &position, fd);
		                    switch (buffer[position]) {
			                case '\'':
  		                        paint_return_analyzer(fd, buffer, position, CONST_CHAR_PAINT, 0);
			                    return 0;
			                case '\\':
				                flag = 1;
			                    break;	
		                    case EOF:
		                        paint_return_analyzer(fd, buffer, position + SH_ONE_BK, NO_PAINT, 0);
		                        return 0;		
	                        default:
				                if (isdigit(buffer[position]) && buffer[position] != '9' && buffer[position] != '8') {
				                    continue;   
				                }
			                    break;
			                }
                            break;
			            }
		    	        if (flag) {
			                continue;
			            } 
			            break;
		            } else if (memchr(simple_escape, buffer[position], SIZE_SET_SIM_ESC) != NULL) {
		                break;
		            } else {
		                paint_return_analyzer(fd, buffer, position + SH_ONE_BK, NO_PAINT, SH_ONE_BK);
			            return 0;
		            }	                    	    
                    
		        }
		        if (flag_x || flag_u) {
		            continue;
		        }
                break;		
	        }
	        break;
 	    default:
	        if (buffer[position] == EOF) {
	            paint_return_analyzer(fd, buffer, position + SH_ONE_BK, NO_PAINT, 0);
                return 0;   
	        }  
	        continue;  
	    }
    }
    return 0;
}

static int string_token(int *buffer, int size_buf, int position, FILE *fd)
{
    int counter_hex;	
    while (TRUE) {
        if ((buffer = check_give_memory(buffer, &size_buf, position)) == NULL) {
            return -1;
        }
        inc_pos_read_to_buf(buffer, &position, fd);
	    switch (buffer[position]) {
	    case '\"':
	        paint_return_analyzer(fd, buffer, position, CONST_STR_PAINT, 0);
            return 0;  	
        case '\\':
	        while (TRUE) {
		        int flag_x = 0;    
		        int flag_u = 0;
                if ((buffer = check_give_memory(buffer, &size_buf, position)) == NULL) {
                    return -1;
                }
                inc_pos_read_to_buf(buffer, &position, fd);
	            switch (buffer[position]) {
                case 'U':
		        case 'u':
              	    counter_hex = 0;    
	                while (TRUE) {
                        if ((buffer = check_give_memory(buffer, &size_buf, position)) == NULL) {
                            return -1;
                        }
                        inc_pos_read_to_buf(buffer, &position, fd);
			            if (buffer[position] == EOF) {
			                paint_return_analyzer(fd, buffer, position + SH_ONE_BK, NO_PAINT, 0);
			                return 0;
			            }
                        if (isxdigit(buffer[position])) {
		                    counter_hex += 1;
			                continue;
		                } else if (counter_hex % DIV_F == 0 && counter_hex != 0) {
			                switch (buffer[position]) {
		                    case '\"':
                                paint_return_analyzer(fd, buffer, position, CONST_STR_PAINT, 0);
				                return 0;
                            case '\\':
				                flag_u = 1;
				                break;
			                default: 
			                    break;
			                }	
		                } else {
		                    paint_return_analyzer(fd, buffer, position + SH_ONE_BK, NO_PAINT, SH_ONE_BK);
		                    return 0;
		                }
			            break;
		            }
	                break;
		        case 'x':
                    if ((buffer = check_give_memory(buffer, &size_buf, position)) == NULL) {
                        return -1;
                    }
                    inc_pos_read_to_buf(buffer, &position, fd);
		            if (buffer[position] == EOF) {
		                paint_return_analyzer(fd, buffer, position + SH_ONE_BK, NO_PAINT, 0);
                        return 0;
		            }
	                if (isxdigit(buffer[position])) {
		                while (TRUE) {
                            if ((buffer = check_give_memory(buffer, &size_buf, position)) == NULL) {
                                return -1;
                            }
                            inc_pos_read_to_buf(buffer, &position, fd);
	                        switch (buffer[position]) {
			                case '\"': 
			                    paint_return_analyzer(fd, buffer, position, CONST_STR_PAINT, 0);
                                return 0;
			                case '\\':
				                flag_x = 1;
                                break;
			                case EOF:
			                    paint_return_analyzer(fd, buffer, position + SH_ONE_BK, NO_PAINT, 0);	
                                return 0;
			                default:
				                if (isxdigit(buffer[position])) {
				                    continue;
				                }
				                break;
			                }
			                break;
			            }
		            } else {
		                paint_return_analyzer(fd, buffer, position + SH_ONE_BK, NO_PAINT, SH_ONE_BK);
			            return 0;
		            }
                    break;
		        case EOF:
		            paint_return_analyzer(fd, buffer, position + SH_ONE_BK, NO_PAINT, 0);
		            return 0;    
		        default:
		            if (isdigit(buffer[position]) && buffer[position] != '9' && buffer[position] != '8') {
			            int flag = 0;	
	              	    for (int i = 0; i <= 2; i++) {
                            if ((buffer = check_give_memory(buffer, &size_buf, position)) == NULL) {
                                return -1;
                            }
                            inc_pos_read_to_buf(buffer, &position, fd);
		                    switch (buffer[position]) {
			                case '\"':
  		                        paint_return_analyzer(fd, buffer, position, CONST_STR_PAINT, 0);
			                    return 0;
			                case '\\':
				                flag = 1;
			                    break;	
		                    case EOF:
		                        paint_return_analyzer(fd, buffer, position + SH_ONE_BK, NO_PAINT, 0);
		                        return 0;		
	                        default:
				                if (isdigit(buffer[position]) && buffer[position] != '9' && buffer[position] != '8') {
				                    continue;   
				                }
			                    break;
			                }
                            break;
			            }
		    	        if (flag) {
			                continue;
			            } 
			            break;
		            } else if (memchr(simple_escape, buffer[position], SIZE_SET_SIM_ESC) != NULL) {
		                break;
		            } else {
		                paint_return_analyzer(fd, buffer, position + SH_ONE_BK, NO_PAINT, SH_ONE_BK);
			            return 0;
		            }	                    	    

		        }
		        if (flag_x || flag_u) {
		            continue;
		        }
                break;		
	        }
	        break;
	    default:
	        if (buffer[position] == EOF) {
	            paint_return_analyzer(fd, buffer, position + SH_ONE_BK, NO_PAINT, 0);
                return 0;   
	        }  	  
	        continue;    
	    }    
    }
    return 0;
}	

static int equal_sets(int *buffer, int pos_buf_set, char *set) 
{
    for (int i = 0; i <= pos_buf_set; i++) {
        if(buffer[i] != set[i]) {
	        return FALSE;
	    }
    }
    return TRUE;
}

static int is_key(int *buffer, int position) 
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

    switch (position + POS_TO_SIZE) {
    case SIZE_UNS:
        if (equal_sets(buffer, position, uns_word) || equal_sets(buffer, position, comp_word) 
                || equal_sets(buffer, position, gen_word) || equal_sets(buffer, position, volat_word)
                || equal_sets(buffer, position, alas_word) || equal_sets(buffer, position, alof_word)) {
	        return TRUE;
	    } else {
	        return FALSE;
	    }

    case SIZE_VOID:
        return equal_sets(buffer, position, void_word);

    case SIZE_ATOM:
        return equal_sets(buffer, position, atom_word);
 
    case SIZE_BOOL:
        return (equal_sets(buffer, position, bool_word) || equal_sets(buffer, position, while_word));
 
    case SIZE_IMAG:
        return equal_sets(buffer, position, imag_word);
 
    case SIZE_NORET:
        return equal_sets(buffer, position, noret_word);
 
    case SIZE_STASS:
        return equal_sets(buffer, position, stass_word);
 
    case SIZE_THR:
        return equal_sets(buffer, position, thread_word);
    
    default:
        return FALSE;	    
    }
}

static int ident_token(int *buffer, int size_buf, int position, FILE *fd)
{ 
    int flag_sev_ucn = 0;	
    int init = buffer[position];
    while (TRUE) {
        if ((buffer = check_give_memory(buffer, &size_buf, position)) == NULL) {
            return -1;
        }
        switch (init) {
        case '\\':
            init = fgetc(fd);
            position += 1;
            buffer[position] = init;
            if (init == 'u' || init == 'U') {
		        int counter_hex = 0;    
	            while (TRUE) {
                    if ((buffer = check_give_memory(buffer, &size_buf, position)) == NULL) {
                        return -1;
                    }
                    init = fgetc(fd);
		            position += 1;
		            buffer[position] = init;
                    if (isxdigit(init)) {
		                counter_hex += 1;
		            } else if (counter_hex % DIV_F == 0 && counter_hex != 0) {
			            if (isalpha(init) || isdigit(init) || init == '_' || init == '\\') {
			                flag_sev_ucn = 1;	
			                break;
			            }       
		                paint_return_analyzer(fd, buffer, position , IDENT_PAINT, 0);
                        return 0; 
		            } else {
		                paint_return_analyzer(fd, buffer, position + SH_ONE_BK, NO_PAINT, SH_ONE_BK);
		                return 0;
		            }
		        }
	        } else {
		        if (flag_sev_ucn) {
		            paint_return_analyzer(fd, buffer, position + SH_TWO_BK, IDENT_PAINT, SH_TWO_BK);
		            return 0;	
		        }    
	            paint_return_analyzer(fd, buffer, position + SH_ONE_BK, NO_PAINT, SH_ONE_BK);
		        return 0;
	        }
	        break;
        default:
            if (isalpha(init) || isdigit(init) || init == '_') {
	            init = fgetc(fd);
                position += 1;
                buffer[position] = init;
	        } else {
		        position--;    
	            if (is_key(buffer, position)) {
		            paint_return_analyzer(fd, buffer, position, KEY_PAINT, SH_ONE_BK);
		            return 0;
		        } else if (buffer[position - SH_ONE_BK] == EOF) {
                    paint_return_analyzer(fd, buffer, position, IDENT_PAINT, 0);
                    return 0;
                } else {	    
	                paint_return_analyzer(fd, buffer, position, IDENT_PAINT, SH_ONE_BK);
                    return 0;
	            }	 
	        }   
        }
    }	
}

static int comment_new_token(int *buffer, int size_buf, int position, FILE *fd)
{
    while (TRUE) {
        if ((buffer = check_give_memory(buffer, &size_buf, position)) == NULL) {
            return -1;
        }
        inc_pos_read_to_buf(buffer, &position, fd);
	    if (buffer[position] != '\n') {
	        if (buffer[position] == EOF) {
	            paint_return_analyzer(fd, buffer, position + SH_ONE_BK, NO_PAINT, 0);
		        return 0;
	        }	
	        continue;
	    } else {
	        paint_return_analyzer(fd, buffer, position + SH_ONE_BK, COMMENT_PAINT, SH_ONE_BK);
	        break;   
	    }
    }
    return 0;
}	

static int comment_old_token(int *buffer, int size_buf, int position, FILE *fd)
{
    while (TRUE) {
        if ((buffer = check_give_memory(buffer, &size_buf, position)) == NULL) {
            return -1;
        }
        inc_pos_read_to_buf(buffer, &position, fd);
        if (buffer[position] != '*') {
	        if (buffer[position] == EOF) {
	            paint_return_analyzer(fd, buffer, SH_ONE_BK, NO_PAINT, SH_ONE_BK * position);
		    return 1;
	        }	
	        continue;
	    } else {
	        while (TRUE) {
                if ((buffer = check_give_memory(buffer, &size_buf, position)) == NULL) {
                    return -1;
                }
                inc_pos_read_to_buf(buffer, &position, fd);
	            if (buffer[position] == '*') {
	                continue;
	            }
	            if (buffer[position] != '/') {
	                if (buffer[position] == EOF) {
	                    paint_return_analyzer(fd, buffer, SH_ONE_BK, NO_PAINT, SH_ONE_BK * position);
		                return 1;
	                }   	    
	                break;
	            } else {
	                paint_return_analyzer(fd, buffer, position, COMMENT_PAINT, 0);
                    return 0;
	            }
	        }
	        continue;
	    }             
    }
    return 0;
}	

static void out_buf(int *buffer, int position) 
{
    for (int i = 0; i <= position; i++) {
         putchar(buffer[i]);
    }
}	

static void print_buf_def_color(int *buffer, int position, char *paint)
{
    static char *no_paint_code = "\033[0m"; // cancel paint
    printf("%s", paint);
    out_buf(buffer, position);
    printf("%s", no_paint_code);
}       	

static void out_buf_p(int *buffer, int position, char paint)
{
    static char *blue_code = "\033[0;34m"; // key words
    static char *pink_code = "\033[0;35m"; // identificators
    static char *orange_code = "\033[0;33m"; // const int
    static char *yellow_code = "\033[1;33m"; // const char
    static char *green_code = "\033[0;32m"; // const string
    static char *red_code = "\033[0;31m"; // punctuators
    static char *brown_code = "\033[0;33m"; // comments
    
    switch (paint) {
    case IDENT_PAINT:
        print_buf_def_color(buffer, position, pink_code);
	    break;
   
    case KEY_PAINT:
        print_buf_def_color(buffer, position, blue_code);
        break; 	
    
    case CONST_INT_PAINT:
        print_buf_def_color(buffer, position, orange_code);
	    break;

    case CONST_CHAR_PAINT:
        print_buf_def_color(buffer, position, yellow_code);
	    break;

    case CONST_STR_PAINT:
        print_buf_def_color(buffer, position, green_code);
	    break;

    case COMMENT_PAINT:
        print_buf_def_color(buffer, position, brown_code);
	    break;

    case PUNCT_PAINT:
        print_buf_def_color(buffer, position, red_code);
	    break;

    default:
        out_buf(buffer, position);
    }
}	

void analyzer(FILE *fd)
{
    int init;
    while ((init = fgetc(fd)) != EOF) {
        int *buf = malloc(BUF_INIT * sizeof(*buf));
        *buf = init;
        int position = 0;
	    int size = BUF_INIT;
        if (*buf == 'u') {	
	        init = fgetc(fd);
	        position += 1;
	        if (init == EOF) {
                paint_return_analyzer(fd, buf, position + SH_ONE_BK, IDENT_PAINT, 0);
		        continue;
	        }
            buf[1] = init;
            if (buf[1] == '8') {
		        position += 1;    
		        init = fgetc(fd);
	            if (init == EOF) {
		            paint_return_analyzer(fd, buf, position + SH_ONE_BK, IDENT_PAINT, 0);
		            continue;
		        }	
		        buf[2] = init;
                if (isalpha(buf[2]) || isdigit(buf[2]) || buf[2] == '_' || buf[2] == '\\') {
		            int state = ident_token(buf, size, position, fd);
	                if (state == -1) {
		                perror("TOO LONG TOKEN!");
			            return;
		            }
	                continue;	    
		        }
		        if (buf[2] == '\"') {
		            int state = string_token(buf, size, position, fd);
		            if (state == -1) {
		                perror("TOO LONG TOKEN!");
			            return;
		            }
		            continue;
		        }
                paint_return_analyzer(fd, buf, position + SH_ONE_BK, IDENT_PAINT, SH_ONE_BK);
	            continue;	
	        }      
	        if (isalpha(buf[1]) || isdigit(buf[1]) || buf[1] == '\\' || buf[1] == '_') {
	            int state = ident_token(buf, size, position, fd);
	            if (state == -1) {
		            perror("TOO LONG TOKEN!");
		            return;
		        }	
		        continue;
	        }
	        if (buf[1] == '\'') {
	            int state = char_token(buf, size, position, fd);
		        if (state == -1) {
		            perror("TOO LONG TOKEN!");
		            return;
		        }
		        continue;
	        }
	        if (buf[1] == '\"') {
	            int state = string_token(buf, size, position, fd);
		        if (state == -1) {
		            perror("TOO LONG TOKEN!");
	                return;		    
		        }
		    continue;
	        }
            paint_return_analyzer(fd, buf, position + SH_ONE_BK, IDENT_PAINT, SH_ONE_BK);     
	        continue;

	    }   	    
	    if (memchr(set_id_ch_str, *buf, SIZE_SET_ID_CH_STR) != NULL) {
	        init = fgetc(fd);
	        position += 1;
	        if (init == EOF) {
                paint_return_analyzer(fd, buf, position + SH_ONE_BK, IDENT_PAINT, 0);
		        continue;
	        }
            buf[1] = init;
	        if (isalpha(buf[1]) || isdigit(buf[1]) || buf[1] == '_' || buf[1] == '\\') {
	            int state = ident_token(buf, size, position, fd);
		        if (state == -1) {
		            perror("TOO LONG TOKEN!");
		            return;
		        }
		        continue;
	        }
	        if (buf[1] == '\'') {
	            int state = char_token(buf, size, position, fd);
		        if (state == -1) {
		            perror("TOO LONG TOKEN!");
		            return;
		        }
		        continue;
	        }
            if (buf[1] == '\"') {
	            int state = string_token(buf, size, position, fd);
		        if (state == -1) {
		            perror("TOO LONG TOKEN");
		            return;
		        }
		        continue;
	        }
	        paint_return_analyzer(fd, buf, position + SH_ONE_BK, IDENT_PAINT, SH_ONE_BK);
	        continue;
	    }
        if (isalpha(*buf) || *buf == '_' || *buf == '\\') {
	        int state = ident_token(buf, size, position, fd);
	        if (state == -1) {
	            perror("TOO LONG TOKEN!");
	            return;
	        }
	        continue;
	    }
        if (isdigit(*buf) && (*buf != '0')) {
	        int state = int_dec_token(buf, size, position, fd);
	        if (state == -1) {
	            perror("TOO LONG TOKEN!");
	            return;
	        }   
	        continue;
	    }
	    if (*buf == '0') {
	        int state = int_oct_token(buf, size, position, fd);
	        if (state == -1) {
	            perror("TOO LONG TOKEN!");
	            return;
	        }
	        continue;
	    }
	    if (*buf == '\'') {
	        int state = char_token(buf, size, position, fd);
	        if (state == -1) {
	            perror("TOO LONG TOKEN!");
		        return;
	        }
	        continue;
	    }
        if (*buf == '\"') {
	        int state = string_token(buf, size, position, fd);
	        if (state == -1) {
	            perror("TOO LONG TOKEN!");
		        return;
	        }
	        continue;
	    }
	    if (*buf == '/') {
	        init = fgetc(fd);
	        position += 1;
	        if (init == EOF) {
                paint_return_analyzer(fd, buf, position + SH_ONE_BK, PUNCT_PAINT, 0);
		        continue;
	        }
            buf[1] = init;
	        if (buf[1] == '/') {
	            int state = comment_new_token(buf, size, position, fd);
		        if (state == -1) {
		            perror("TOO LONG TOKEN!");
		            return;
		        }
		        continue;
	        }  
            if (buf[1] == '*') {
	            int state = comment_old_token(buf, size, position, fd);
		        if (state == -1) {
		            perror("TOO LONG TOKEN!");
		            return;
		        }
		        if (state == 1) {
		            buf = malloc(BUF_INIT * sizeof(*buf));
	                *buf = fgetc(fd);
                    position = 0;
	                size = BUF_INIT;
		            paint_return_analyzer(fd, buf, position, PUNCT_PAINT, 0);
	                continue;
		        }
		        continue;
	        } 
	        paint_return_analyzer(fd, buf, position + SH_ONE_BK, PUNCT_PAINT, SH_ONE_BK);
	        continue;

	    }
        if (memchr(punctuators, *buf, SIZE_SET_PUNCT) != NULL) {
            paint_return_analyzer(fd, buf, position, PUNCT_PAINT, 0);
	        continue;
        }
	    putchar(*buf);  
        free(buf);
    }	   
    return;
}	
