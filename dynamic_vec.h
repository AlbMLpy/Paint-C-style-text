/**
 * This is a dynamic container for int values with interface below;
 */ 
struct Dynamic_Vec;
typedef struct Dynamic_Vec Dynamic_Vec;
/**
 * This function initializes dynamic vector with fixed size;
 * Returns pointer on container if memory is not full, else NULL;
 */ 
Dynamic_Vec *
Dynamic_Vec_initialize_vec(void);

/**
 * This function returns the size of vec, if vec == NULL it returns -1;
 */
int
Dynamic_Vec_size_vec(Dynamic_Vec *vec);

/**
 * This function free the memory given to vec pointer;
 */
void
Dynamic_Vec_finalize_vec(Dynamic_Vec *vec);

/**
 * This function allows you to put data into vec knowing index in dynamic container;
 * Returns changed pointer vec if there are no problems with memory, else vec = NULL, 
 * and function returns NULL;
 */
Dynamic_Vec *
Dynamic_Vec_set_value_vec(Dynamic_Vec *vec, int index, int data);

/**
 * This function allows you to take data from vec knowing index in dynamic container;
 * Returns 0 and put int data into *data if such index is regular, else returns -1; 
 */
int
Dynamic_Vec_get_value_vec(Dynamic_Vec *vec, int index, int *data);

/**
 * This function prints contents of vec like digits to standart output;
 * If vec == NULL it does nothing; if index_begin and index_end are not appropriate 
 * function returns -1, else prints contents and returns 0;
 */
int
Dynamic_Vec_print_dyn_vec_digit(Dynamic_Vec *vec, int index_begin, int index_end);

/**
 * This function prints contents of vec like characters to standart output;
 * If vec == NULL it does nothing; if index_begin and index_end are not appropriate 
 * function returns -1, else prints contents and returns 0;
 */
int
Dynamic_Vec_print_dyn_vec_text(Dynamic_Vec *vec, int index_begin, int index_end);

